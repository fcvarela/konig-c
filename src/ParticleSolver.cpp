#include <stdlib.h>

#include "clutils.h"
#include "ParticleSolver.h"

using namespace konig;

const char *cl_kernel_src[] = {
    "typedef struct {\n",
    "    float3 pos;\n",
    "    float3 vel;\n",
    "} vertex_t;\n",
    "\n",
    "__kernel void vertex_step(__global vertex_t *in, __global vertex_t *out, const float dt) {\n",
    "    int id = get_global_id(0);\n",
    "    out[id].pos = in[id].pos + in[id].vel * dt;\n",
    "    out[id].vel = in[id].vel;\n",
    "}\n"
};

void ParticleSolver::pick_device() {
    // get platform count
    cl_uint platform_count;
    cl_platform_id *platforms;
    cl_device_id* devices;
    cl_uint deviceCount;
    char* value;
    size_t valueSize;
    cl_uint computeUnits;
    cl_uint maxComputeUnits = 0;

    fprintf(stderr, "OpenGL renderer: %s\n", glGetString(GL_RENDERER));

    clGetPlatformIDs(1, &this->platform, NULL);

    clGetDeviceIDs(this->platform, CL_DEVICE_TYPE_ALL, 0, NULL, &deviceCount);
    devices = (cl_device_id*) malloc(sizeof(cl_device_id) * deviceCount);
    clGetDeviceIDs(this->platform, CL_DEVICE_TYPE_ALL, deviceCount, devices, NULL);

        // for each device print critical attributes
    for (int j = 0; j < deviceCount; j++) {
            // print device name
        clGetDeviceInfo(devices[j], CL_DEVICE_NAME, 0, NULL, &valueSize);
        value = (char*) malloc(valueSize);
        clGetDeviceInfo(devices[j], CL_DEVICE_NAME, valueSize, value, NULL);
        printf("%d. Device: %s\n", j+1, value);
        free(value);

            // print hardware device version
        clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, 0, NULL, &valueSize);
        value = (char*) malloc(valueSize);
        clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, valueSize, value, NULL);
        printf(" %d.%d Hardware version: %s\n", j+1, 1, value);
        free(value);

            // print software driver version
        clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, 0, NULL, &valueSize);
        value = (char*) malloc(valueSize);
        clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, valueSize, value, NULL);
        printf(" %d.%d Software version: %s\n", j+1, 2, value);
        free(value);

            // print c version supported by compiler for device
        clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, 0, NULL, &valueSize);
        value = (char*) malloc(valueSize);
        clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, valueSize, value, NULL);
        printf(" %d.%d OpenCL C version: %s\n", j+1, 3, value);
        free(value);

            // print parallel compute units
        clGetDeviceInfo(devices[j], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(computeUnits), &computeUnits, NULL);
        printf(" %d.%d Parallel compute units: %d\n", j+1, 4, computeUnits);

        if (computeUnits > maxComputeUnits) {
            this->device = devices[j];
        }
    }
    free(devices);
}

ParticleSolver::ParticleSolver() {
    // select device w/ max compute units
    pick_device();

    //bootstrap from that
    #if defined ( __APPLE__ ) || defined ( MACOSX )
    cl_context_properties properties [] = {
        CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
        ( cl_context_properties ) CGLGetShareGroup ( CGLGetCurrentContext ( ) ),
        0
    };
    #elif defined ( WIN32 )
    cl_context_properties properties [] = {
        CL_CONTEXT_PLATFORM, ( cl_context_properties ) this->platform,
        CL_GL_CONTEXT_KHR, ( cl_context_properties ) wglGetCurrentContext ( ),
        CL_WGL_HDC_KHR, ( cl_context_properties ) wglGetCurrentDC ( ),
        0
    };
    #else
    cl_context_properties properties [] = {
        CL_GL_CONTEXT_KHR, ( cl_context_properties ) glXGetCurrentContext ( ),
        CL_GLX_DISPLAY_KHR, ( cl_context_properties ) glXGetCurrentDisplay ( ),
        CL_CONTEXT_PLATFORM, ( cl_context_properties ) this->platform,
        0
    };
    #endif

    cl_int status;
    this->context = clCreateContext(properties, 1, &this->device, NULL, NULL, &status);
    if (status != CL_SUCCESS) {
        fprintf(stderr, "clCreateContext: %s\n", get_error_string(status));
        exit(1);
    }
    this->queue = clCreateCommandQueue(context, this->device, 0, &status);
    if (status != CL_SUCCESS) {
        fprintf(stderr, "clCreateCommandQueue: %s\n", get_error_string(status));
        exit(1);
    }

    this->program = clCreateProgramWithSource(this->context, sizeof(cl_kernel_src)/sizeof(*cl_kernel_src), cl_kernel_src, NULL, &status);
    if (status != CL_SUCCESS) {
        fprintf(stderr, "clCreateProgramWithSource: %s\n", get_error_string(status));
        exit(1);
    }
    
    status = clBuildProgram(this->program, 0, NULL, NULL, NULL, NULL);
    if (status != CL_SUCCESS) {
        char buffer[10240];
        clGetProgramBuildInfo(this->program, this->device, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, NULL);
        fprintf(stderr, "clBuildProgram: CL Compilation failed:\n%s", buffer);
        exit(1);
    }

    this->kernel = clCreateKernel(this->program, "vertex_step", &status);
    if (!this->kernel || status != CL_SUCCESS) {
        fprintf(stderr, "clCreateKernel: %s\n", get_error_string(status));
        exit(1);
    }
}

ParticleSolver::~ParticleSolver() {
    clReleaseKernel(this->kernel);
    clReleaseProgram(program);
    clReleaseContext(context);
}

void ParticleSolver::step(std::vector<vertex_t>&vertex_array, float dt) {
    // allocate buffers
    size_t data_size = sizeof(vertex_t) * vertex_array.size();
    cl_mem input_buffer = clCreateBuffer(this->context, CL_MEM_READ_ONLY, data_size, NULL, NULL);
    cl_mem output_buffer = clCreateBuffer(this->context, CL_MEM_WRITE_ONLY, data_size, NULL, NULL);

    // schedule vertex_array -> input_buffer
    clEnqueueWriteBuffer(queue, input_buffer, CL_TRUE, 0, data_size, (void *)&vertex_array[0], 0, NULL, NULL);

    // set kernel args
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &input_buffer);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), &output_buffer);
    clSetKernelArg(kernel, 2, sizeof(float), &dt);
    
    // schedule the kernel
    size_t global_work_size = vertex_array.size()*sizeof(vertex_t);
    cl_event kernel_completion;
    clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_work_size, NULL, 0, NULL, &kernel_completion);
    clWaitForEvents(1, &kernel_completion);
    clReleaseEvent(kernel_completion);

    clEnqueueReadBuffer(queue, output_buffer, CL_TRUE, 0, data_size, (void *)&vertex_array[0], 0, NULL, NULL);

    // read memory back
    clReleaseMemObject(input_buffer);
    clReleaseMemObject(output_buffer);
}
