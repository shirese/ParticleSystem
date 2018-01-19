#include "clmanager.h"
#include "utils.h"

CLManager::CLManager()
{
    int err;

    std::vector<cl::Platform> all_platforms;
    cl::Platform::get(&all_platforms);

    if (all_platforms.size()==0) {
        std::cout<<" No platforms found. Check OpenCL installation!" << std::endl;
        exit(1);
    }
    cl::Platform default_platform=all_platforms[0];
    std::cout << "Using platform: "<< default_platform.getInfo<CL_PLATFORM_NAME>() << std::endl;

    // get default device (CPUs, GPUs) of the default platform
    std::vector<cl::Device> all_devices;
    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if (all_devices.size() == 0) {
        std::cout<<" No devices found. Check OpenCL installation!" << std::endl;
        exit(1);
    }

    // use device[1] because that's a GPU; device[0] is the CPU
    cl::Device default_device=all_devices[1];
    std::cout<< "Using device: " << default_device.getInfo<CL_DEVICE_NAME>() << std::endl;

    // a context is like a "runtime link" to the device and platform;
    // i.e. communication is possible
    m_context = cl::Context({default_device});

    // Compute te program using the kernels

    cl::Program::Sources sources;
    std::string source[3];

    printf("Loading kernel header from file '%s'...\n", KERNEL_HEADER); 
    source[0] = fileToString(KERNEL_HEADER);
    if (source[0].empty())
        exit(-1);
    sources.push_back({source[0].c_str(), source[0].length()});
    printf("Loading kernel main from file '%s'...\n", KERNEL_MAIN);
    source[1] = fileToString(KERNEL_MAIN);
    if (source[1].empty())
        exit(-1);
    sources.push_back({source[1].c_str(), source[1].length()});
    printf("Loading kernel update from file '%s'...\n", KERNEL_UPDATE);
    source[2] = fileToString(KERNEL_UPDATE);
    if (source[2].empty())
        exit(-1);
    sources.push_back({source[2].c_str(), source[2].length()});

    //  Build the program

    cl::Program program(m_context, sources);
    if (program.build({default_device}) != CL_SUCCESS) {
        std::cout << "Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device) << std::endl;
        exit(1);
    }

    // Create the kernels from withing the program
    printf("Creating kernel '%s'...\n", KERNEL_INIT_METHOD_NAME);
    cl::Kernel initKernel(program, KERNEL_INIT_METHOD_NAME, &err);
    if (err != CL_SUCCESS)
    {
        printf("OpenCL init kernel error: %d", err);
        exit(-1);
    }
    printf("Creating kernel '%s'...\n", KERNEL_UPDATE_METHOD_NAME);
    cl::Kernel updateKernel(program, KERNEL_UPDATE_METHOD_NAME, &err);
    if (err != CL_SUCCESS)
    {
        printf("OpenCL update kernel error: %d", err);
        exit(-1);
    }

    // Get the maximum work group size for executing the kernels on the device
	cl_int maxWorkGroupSize = initKernel.getWorkGroupInfo<CL_KERNEL_WORK_GROUP_SIZE>(default_device, &err);
	if (err != CL_SUCCESS)
	{
		printf("Error: Failed to retrieve kernel work group info! %d\n", err);
		exit(-1);
	}
	printf("Maximum Workgroup Size '%d'\n", maxWorkGroupSize);

	maxWorkGroupSize = updateKernel.getWorkGroupInfo<CL_KERNEL_WORK_GROUP_SIZE>(default_device, &err);
	if (err != CL_SUCCESS)
	{
		printf("Error: Failed to retrieve kernel work group info! %d\n", err);
		exit(-1);
	}
	printf("Maximum Workgroup Size '%d'\n", maxWorkGroupSize);

}

void CLManager::computeMemory(  ParticleManager &particleManager)
{
    int err;

    printf("Allocating buffers on compute device.\n");
    m_bufferVBO = cl::BufferGL(m_context, CL_MEM_READ_WRITE, particleManager.getVBO(), &err);
    if (err < 0)
    {
        printf("Couldn't create a buffer object from the VBO.");
        exit(-1);
    }
    m_bufferGravity = cl::Buffer(m_context, CL_MEM_READ_ONLY, sizeof(float) * 3, NULL, &err);
    if (err < 0)
    {
        printf("Couldn't create gravity buffer.");
        exit(-1);
    }
    err = m_initKernel.setArg(0, sizeof(m_bufferVBO), &m_bufferVBO);
    if (err < 0)
    {
        printf("Couldn't set init kernel arg.");
        exit(-1);
    }
    err = m_updateKernel.setArg(0, sizeof(m_bufferVBO), &m_bufferVBO);
    if (err < 0)
    {
        printf("Couldn't set update kernel arg (VBO).");
        exit(-1);
    }
    err = m_updateKernel.setArg(0, sizeof(m_bufferGravity), &m_bufferGravity);
    if (err < 0)
    {
        printf("Couldn't set update kernel arg (buffer gravity).");
        exit(-1);
    }
}
