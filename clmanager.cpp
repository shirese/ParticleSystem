#include "clmanager.h"
#include "utils.h"

void CLManager::initCL(QOpenGLContext *glContext)
{
    int err;

    if (!glContext) {
        qWarning("Attempted CL-GL interop without a current OpenGL context");
        exit(-1);
    }
    
    std::vector<cl::Platform> all_platforms;
    cl::Platform::get(&all_platforms);

    if (all_platforms.size()==0) {
        std::cout<<" No platforms found. Check OpenCL installation!" << std::endl;
        exit(1);
    }
    cl::Platform platform=all_platforms[0];
    std::cout << "Using platform: "<< platform.getInfo<CL_PLATFORM_NAME>() << std::endl;

    // get default device (CPUs, GPUs) of the default platform
    std::vector<cl::Device> all_devices;
    platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if (all_devices.size() == 0) {
        std::cout<<" No devices found. Check OpenCL installation!" << std::endl;
        exit(1);
    }
    
    // use device[1] because that's a GPU; device[0] is the CPU
    cl::Device default_device=all_devices[1];
    std::cout<< "Using device: " << default_device.getInfo<CL_DEVICE_NAME>() << std::endl;

    printf("Using active OpenGL context...\n");

    // CGLSetCurrentContext((CGLContextObj)(glContext->currentContext()));
    CGLContextObj kCGLContext = CGLGetCurrentContext();
    CGLShareGroupObj kCGLShareGroup = CGLGetShareGroup(kCGLContext);

	cl_context_properties properties[] = { 
		CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE, 
		(cl_context_properties)kCGLShareGroup,
        0
	};

	// Create a context from a CGL share group
    m_context = cl::Context(default_device, properties, clLogMessagesToStdoutAPPLE, 0, &err);

    if (err != CL_SUCCESS)
    {
        std::cout << "Error creating context: " << err << std::endl;
        exit(-1);
    }

    // Create a command queue
    m_cmdQueue = cl::CommandQueue(m_context, default_device, 0, &err);
    if (err != CL_SUCCESS)
    {
        std::cout << "Error creating command queue: " << err << std::endl;
        exit(-1);
    }
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
    m_initKernel = cl::Kernel(program, KERNEL_INIT_METHOD_NAME, &err);
    if (err != CL_SUCCESS)
    {
        printf("OpenCL init kernel error: %d", err);
        exit(-1);
    }
    printf("Creating kernel '%s'...\n", KERNEL_UPDATE_METHOD_NAME);
    m_updateKernel = cl::Kernel(program, KERNEL_UPDATE_METHOD_NAME, &err);
    if (err != CL_SUCCESS)
    {
        printf("OpenCL update kernel error: %d", err);
        exit(-1);
    }

    // Get the maximum work group size for executing the kernels on the device
	m_maxWorkGroupSize = m_initKernel.getWorkGroupInfo<CL_KERNEL_WORK_GROUP_SIZE>(default_device, &err);
	if (err != CL_SUCCESS)
	{
		printf("Error: Failed to retrieve kernel work group info! %d\n", err);
		exit(-1);
	}
	printf("Init kernel maximum Workgroup Size '%d'\n", m_maxWorkGroupSize);

	m_maxWorkGroupSize = m_updateKernel.getWorkGroupInfo<CL_KERNEL_WORK_GROUP_SIZE>(default_device, &err);
	if (err != CL_SUCCESS)
	{
		printf("Error: Failed to retrieve kernel work group info! %d\n", err);
		exit(-1);
	}
	printf("Update kernel maximum Workgroup Size '%d'\n", m_maxWorkGroupSize);

}

void CLManager::computeMemory(QOpenGLBuffer &posVBO)
{
    int err;

    printf("Allocating buffers on compute device.\n");
    m_bufferVBO = cl::BufferGL(m_context, CL_MEM_READ_WRITE, posVBO.bufferId(), &err);
    if (err < 0)
    {
        printf("Couldn't create a buffer object from the VBO.");
        exit(-1);
    }
    m_bufferShape = cl::Buffer(m_context, CL_MEM_READ_WRITE, sizeof(short), NULL, &err);
    if (err < 0)
    {
        printf("Couldn't create shape buffer.");
        exit(-1);
    }
    m_bufferGravity = cl::Buffer(m_context, CL_MEM_READ_ONLY, sizeof(float) * 3, NULL, &err);
    if (err < 0)
    {
        printf("Couldn't create gravity buffer.");
        exit(-1);
    }
    err = m_initKernel.setArg(0, m_bufferVBO);
    if (err < 0)
    {
        printf("Couldn't set init kernel arg.");
        exit(-1);
    }
    err = m_initKernel.setArg(1, m_bufferShape);
    if (err < 0)
    {
        printf("Couldn't set init kernel arg.");
        exit(-1);
    }
    err = m_updateKernel.setArg(0, m_bufferVBO);
    if (err < 0)
    {
        printf("Couldn't set update kernel arg (VBO).");
        exit(-1);
    }
    err = m_updateKernel.setArg(1, m_bufferGravity);
    if (err < 0)
    {
        printf("Couldn't set update kernel arg (buffer gravity).");
        exit(-1);
    }
}

void CLManager::runUpdateKernel(float *gravityPoint)
{
    int err;
    cl::Event event;

	glFinish();
    m_vbos.push_back(m_bufferVBO);
    // printf("Running update kernel...\n");

    // PARTICLES
    err = m_cmdQueue.enqueueAcquireGLObjects(&m_vbos, NULL, NULL);
	// err = clEnqueueAcquireGLObjects(computeCommands, 1, &m_bufferVBO, 0, 0, NULL);
	if (err < 0)
	{
		printf("Couldn't acquire the GL objects: %d", err);
		exit(-1);
	}

	// err = clEnqueueWriteBuffer(computeCommands, gravityPointMemObject, CL_TRUE,  0, sizeof(float) * 3, test, 0, NULL, NULL);
    err = m_cmdQueue.enqueueWriteBuffer(m_bufferGravity, CL_TRUE, 0, sizeof(float) * 3, gravityPoint, nullptr, &event);
	if (err < 0) {
		printf("Couldn't write into the gravity point openCL buffer: %d", err);
		exit(-1);
    }

    size_t globalWorkSize = PARTICLES_COUNT;
    // size_t globalWorkSize = 1024;
    // err = clEnqueueNDRangeKernel(m_cmdQueue(), m_updateKernel(), 1, nullptr, &globalWorkSize, &m_maxWorkGroupSize, 0, nullptr, &event());
    err = m_cmdQueue.enqueueNDRangeKernel(m_updateKernel, cl::NullRange, cl::NDRange(globalWorkSize), cl::NullRange, nullptr, &event);
	if (err < 0)
	{
		printf("Couldn't enqueue the kernel: %d", err);
		exit(-1);
	}
	err = event.wait();
	if (err < 0)
	{
		printf("Wait event error %d", err);
		exit(-1);
	}
    // err = m_cmdQueue.enqueueReleaseGLObjects(&m_vbos);
	// clEnqueueReleaseGLObjects(computeCommands, 1, &m_bufferVBO, 0, NULL, NULL);
    // clReleaseEvent(waitEvent);
}

void CLManager::runInitKernel()
{
    int err;
	cl::Event event;
    
	glFinish();
    m_vbos.push_back(m_bufferVBO);
	/* Execute the kernel */
    err = m_cmdQueue.enqueueAcquireGLObjects(&m_vbos, NULL, NULL);
	if (err < 0)
	{
		printf("Couldn't acquire the GL objects: %d", err);
		exit(-1);
	}
    err = m_cmdQueue.enqueueWriteBuffer(m_bufferShape, CL_TRUE, 0, sizeof(short), &shape, nullptr, &event);
	if (err < 0) {
		printf("Couldn't write into shape buffer: %d", err);
		exit(-1);
    }
	size_t globalWorkSize = PARTICLES_COUNT;
	// size_t globalWorkSize = 1024;
    err = m_cmdQueue.enqueueNDRangeKernel(m_initKernel, cl::NullRange, cl::NDRange(globalWorkSize), cl::NullRange, nullptr, &event);
	// err = clEnqueueNDRangeKernel(m_cmdQueue(), m_initKernel(), 1, nullptr, &globalWorkSize, &m_maxWorkGroupSize, 0, nullptr, &event());
	if (err < 0)
	{
		printf("Couldn't enqueue the kernel: %d", err);
		exit(-1);
	}
	err = event.wait();
	if (err < 0)
	{
		printf("Wait event error: %d", err);
    		exit(-1);
    }
    // err = m_cmdQueue.enqueueReleaseGLObjects(&m_vbos);
    // if (err < 0)
	// {
	// 	printf("Release error: %d", err);
	// 	exit(-1);
    // }
    err = m_cmdQueue.enqueueReadBuffer(m_bufferShape, CL_TRUE, 0, sizeof(short), &shape, nullptr, &event);
	if (err < 0) {
		printf("Couldn't read into shape buffer: %d", err);
		exit(-1);
    }
}
