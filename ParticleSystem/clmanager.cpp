#include "clmanager.h"

CLManager::CLManager()
{
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
    cl::Device default_device = all_devices[1];
    std::cout<< "Using device: " << default_device.getInfo<CL_DEVICE_NAME>() << std::endl;

    // a context is like a "runtime link" to the device and platform;
    // i.e. communication is possible
    cl::Context context({default_device});
}
