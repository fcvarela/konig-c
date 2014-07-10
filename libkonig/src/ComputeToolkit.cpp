#include <string>
#include <utility>

#include "gl.h"
#include "ComputeToolkit.h"

std::map<uint8_t, std::string> ComputeToolkit::get_devices() {
    // get a platform
    cl_platform_id platform;
    clGetPlatformIDs(1, &platform, NULL);

    // iterate through platform device list and append to map
    std::map<uint8_t, std::string> device_list;

    cl_uint device_count;
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU|CL_DEVICE_HOST_UNIFIED_MEMORY, 0, NULL, &device_count);

    cl_device_id* devices = (cl_device_id*)malloc(sizeof(cl_device_id)*device_count);
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU|CL_DEVICE_HOST_UNIFIED_MEMORY, device_count, devices, NULL);

    char* value;
    size_t valueSize;
    // for each device print critical attributes
    for (uint8_t j = 0; j < device_count; j++) {
        // print device name
        clGetDeviceInfo(devices[j], CL_DEVICE_NAME, 0, NULL, &valueSize);
        value = (char*) malloc(valueSize);
        clGetDeviceInfo(devices[j], CL_DEVICE_NAME, valueSize, value, NULL);
        printf("%d. Device: %s\n", j+1, value);
        std::string device_name(value);
        free(value);

        // print parallel compute units
        // clGetDeviceInfo(devices[j], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(computeUnits), &computeUnits, NULL);
        // printf(" %d.%d Parallel compute units: %d\n", j+1, 4, computeUnits);
        device_list.insert(std::pair<uint8_t, std::string>(j, device_name));
    }

    free(devices);

    return device_list;
}