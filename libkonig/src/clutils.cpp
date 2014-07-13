#include <stdlib.h>
#include <stdio.h>
#include "clutils.h"

#define MAX_SOURCE_SIZE (0x100000)

cl_platform_id clutils__get_default_platform() {
    cl_platform_id pid;
    clGetPlatformIDs(1, &pid, NULL);
    return pid;
}

cl_device_id clutils__get_default_device(cl_platform_id platform) {
    cl_uint deviceCount = 0;
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU|CL_DEVICE_HOST_UNIFIED_MEMORY, 0, NULL, &deviceCount);

    cl_device_id *devices = (cl_device_id*)malloc(sizeof(cl_device_id) * deviceCount);
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU|CL_DEVICE_HOST_UNIFIED_MEMORY, deviceCount, devices, NULL);
    cl_device_id device = devices[deviceCount-1];
    free(devices);

    return device;
}

cl_context clutils__make_context(cl_platform_id platform, cl_device_id device) {
    //bootstrap from that
    #if defined ( __APPLE__ ) || defined ( MACOSX )
    cl_context_properties properties [] = {
        CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
        ( cl_context_properties ) CGLGetShareGroup ( CGLGetCurrentContext ( ) ),
        0
    };
    #elif defined ( WIN32 )
    cl_context_properties properties [] = {
        CL_CONTEXT_PLATFORM, ( cl_context_properties ) platform,
        CL_GL_CONTEXT_KHR, ( cl_context_properties ) wglGetCurrentContext ( ),
        CL_WGL_HDC_KHR, ( cl_context_properties ) wglGetCurrentDC ( ),
        0
    };
    #else
    cl_context_properties properties [] = {
        CL_GL_CONTEXT_KHR, ( cl_context_properties ) glXGetCurrentContext ( ),
        CL_GLX_DISPLAY_KHR, ( cl_context_properties ) glXGetCurrentDisplay ( ),
        CL_CONTEXT_PLATFORM, ( cl_context_properties ) platform,
        0
    };
    #endif

    cl_int status;
    cl_context context = clCreateContext(properties, 1, &device, NULL, NULL, &status);
    if (status != CL_SUCCESS) {
        fprintf(stderr, "clCreateContext: %s\n", clutils__get_error_string(status));
        exit(1);
    }
    return context;
}

cl_command_queue clutils__make_command_queue(cl_context context, cl_device_id device) {
    cl_int status;
    cl_command_queue queue = clCreateCommandQueue(context, device, 0, &status);
    if (status != CL_SUCCESS) {
        fprintf(stderr, "clCreateCommandQueue: %s\n", clutils__get_error_string(status));
        exit(1);
    }
    return queue;
}

cl_program clutils__load_program(cl_context context, cl_device_id device, const char *filename) {
    // load the kernel from file
    FILE *fp = fopen(filename, "rt");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }

    char *source_str = (char*)malloc(MAX_SOURCE_SIZE);
    size_t source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose(fp);

    cl_int status;
    cl_program program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &status);
    if (status != CL_SUCCESS) {
        fprintf(stderr, "clCreateProgramWithSource: %s\n", clutils__get_error_string(status));
        exit(1);
    }

    status = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    if (status != CL_SUCCESS) {
        char buffer[10240];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, NULL);
        fprintf(stderr, "clBuildProgram: CL Compilation failed:\n%s", buffer);
        exit(1);
    }

    free(source_str);
    return program;
}

cl_kernel clutils__load_kernel(cl_program program, const char *kernel_name) {
    cl_int status;
    cl_kernel kernel = clCreateKernel(program, kernel_name, &status);
    if (!kernel || status != CL_SUCCESS) {
        fprintf(stderr, "clCreateKernel (%s): %s\n", kernel_name, clutils__get_error_string(status));
        exit(1);
    }

    return kernel;
}

const char * clutils__get_error_string(cl_int err) {
    switch(err){
        case 0: return "CL_SUCCESS";
        case -1: return "CL_DEVICE_NOT_FOUND";
        case -2: return "CL_DEVICE_NOT_AVAILABLE";
        case -3: return "CL_COMPILER_NOT_AVAILABLE";
        case -4: return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
        case -5: return "CL_OUT_OF_RESOURCES";
        case -6: return "CL_OUT_OF_HOST_MEMORY";
        case -7: return "CL_PROFILING_INFO_NOT_AVAILABLE";
        case -8: return "CL_MEM_COPY_OVERLAP";
        case -9: return "CL_IMAGE_FORMAT_MISMATCH";
        case -10: return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
        case -11: return "CL_BUILD_PROGRAM_FAILURE";
        case -12: return "CL_MAP_FAILURE";
        case -30: return "CL_INVALID_VALUE";
        case -31: return "CL_INVALID_DEVICE_TYPE";
        case -32: return "CL_INVALID_PLATFORM";
        case -33: return "CL_INVALID_DEVICE";
        case -34: return "CL_INVALID_CONTEXT";
        case -35: return "CL_INVALID_QUEUE_PROPERTIES";
        case -36: return "CL_INVALID_COMMAND_QUEUE";
        case -37: return "CL_INVALID_HOST_PTR";
        case -38: return "CL_INVALID_MEM_OBJECT";
        case -39: return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
        case -40: return "CL_INVALID_IMAGE_SIZE";
        case -41: return "CL_INVALID_SAMPLER";
        case -42: return "CL_INVALID_BINARY";
        case -43: return "CL_INVALID_BUILD_OPTIONS";
        case -44: return "CL_INVALID_PROGRAM";
        case -45: return "CL_INVALID_PROGRAM_EXECUTABLE";
        case -46: return "CL_INVALID_KERNEL_NAME";
        case -47: return "CL_INVALID_KERNEL_DEFINITION";
        case -48: return "CL_INVALID_KERNEL";
        case -49: return "CL_INVALID_ARG_INDEX";
        case -50: return "CL_INVALID_ARG_VALUE";
        case -51: return "CL_INVALID_ARG_SIZE";
        case -52: return "CL_INVALID_KERNEL_ARGS";
        case -53: return "CL_INVALID_WORK_DIMENSION";
        case -54: return "CL_INVALID_WORK_GROUP_SIZE";
        case -55: return "CL_INVALID_WORK_ITEM_SIZE";
        case -56: return "CL_INVALID_GLOBAL_OFFSET";
        case -57: return "CL_INVALID_EVENT_WAIT_LIST";
        case -58: return "CL_INVALID_EVENT";
        case -59: return "CL_INVALID_OPERATION";
        case -60: return "CL_INVALID_GL_OBJECT";
        case -61: return "CL_INVALID_BUFFER_SIZE";
        case -62: return "CL_INVALID_MIP_LEVEL";
        case -63: return "CL_INVALID_GLOBAL_WORK_SIZE";
        default: return "Unknown OpenCL error";
    }
}
