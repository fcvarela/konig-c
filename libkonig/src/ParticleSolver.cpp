#include <stdlib.h>

#include "clutils.h"
#include "ParticleSolver.h"

#define MAX_SOURCE_SIZE (0x100000)

using namespace konig;

void ParticleSolver::load_kernel() {
    // load the kernel from file
    FILE *fp = fopen("data/kernels/graphtopo.cl", "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }
    char *source_str = (char*)malloc(MAX_SOURCE_SIZE);
    size_t source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose(fp);

    cl_int status;
    this->program = clCreateProgramWithSource(this->context, 1, (const char **)&source_str, (const size_t *)&source_size, &status);
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

    this->vertices_kernel = clCreateKernel(this->program, "vertex_step", &status);
    if (!this->vertices_kernel || status != CL_SUCCESS) {
        fprintf(stderr, "clCreateKernel: %s\n", get_error_string(status));
        exit(1);
    }

    this->edges_kernel = clCreateKernel(this->program, "edge_step", &status);
    if (!this->edges_kernel || status != CL_SUCCESS) {
        fprintf(stderr, "clCreateKernel: %s\n", get_error_string(status));
        exit(1);
    }

    this->sum_kernel = clCreateKernel(this->program, "integrate", &status);
    if (!this->sum_kernel || status != CL_SUCCESS) {
        fprintf(stderr, "clCreateKernel: %s\n", get_error_string(status));
        exit(1);
    }
}

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
    this->device = devices[2];
    free(devices);
}

void ParticleSolver::init_context() {
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
}

ParticleSolver::ParticleSolver() {
    // select device w/ max compute units
    pick_device();
    init_context();
    load_kernel();
}

ParticleSolver::~ParticleSolver() {
    clReleaseKernel(this->vertices_kernel);
    clReleaseKernel(this->edges_kernel);
    clReleaseKernel(this->sum_kernel);
    clReleaseProgram(program);
    clReleaseContext(context);
}

void ParticleSolver::step(GLuint vbo_in, GLuint vbo_out, GLuint edge_vbo, size_t vertex_element_count, size_t edge_element_count, float dt) {
    // solve vertex
    this->cl_vbo_in = clCreateFromGLBuffer(this->context, CL_MEM_READ_ONLY, vbo_in, NULL);
    this->cl_vbo_out = clCreateFromGLBuffer(this->context, CL_MEM_READ_WRITE, vbo_out, NULL);
    this->cl_edge_vbo = clCreateFromGLBuffer(this->context, CL_MEM_READ_ONLY, edge_vbo, NULL);

    clEnqueueAcquireGLObjects(this->queue, 1, &this->cl_vbo_in, 0, 0, 0);
    clEnqueueAcquireGLObjects(this->queue, 1, &this->cl_vbo_out, 0, 0, 0);
    clEnqueueAcquireGLObjects(this->queue, 1, &this->cl_edge_vbo, 0, 0, 0);

    // vertices
    clSetKernelArg(vertices_kernel, 0, sizeof(cl_mem), (void *)&this->cl_vbo_in);
    clSetKernelArg(vertices_kernel, 1, sizeof(cl_mem), (void *)&this->cl_vbo_out);
    cl_int status = clEnqueueNDRangeKernel(queue, vertices_kernel, 1, NULL, &vertex_element_count, NULL, 0, 0, 0);

    // edges
    clSetKernelArg(edges_kernel, 0, sizeof(cl_mem), (void *)&this->cl_edge_vbo);
    clSetKernelArg(edges_kernel, 1, sizeof(cl_mem), (void *)&this->cl_vbo_in);
    clSetKernelArg(edges_kernel, 2, sizeof(cl_mem), (void *)&this->cl_vbo_out);
    status = clEnqueueNDRangeKernel(queue, edges_kernel, 1, NULL, &edge_element_count, NULL, 0, 0, 0);

    // integrate
    clSetKernelArg(sum_kernel, 0, sizeof(cl_mem), (void *)&this->cl_vbo_in);
    clSetKernelArg(sum_kernel, 1, sizeof(cl_mem), (void *)&this->cl_vbo_out);
    clSetKernelArg(sum_kernel, 2, sizeof(float), &dt);
    status = clEnqueueNDRangeKernel(queue, sum_kernel, 1, NULL, &vertex_element_count, NULL, 0, 0, 0);

    clEnqueueReleaseGLObjects(queue, 1, &this->cl_vbo_in, 0, 0, 0);
    clEnqueueReleaseGLObjects(queue, 1, &this->cl_vbo_out, 0, 0, 0);
    clEnqueueReleaseGLObjects(queue, 1, &this->cl_edge_vbo, 0, 0, 0);
}
