#include <stdlib.h>

#include "ParticleSolver.h"

namespace konig {

ParticleSolver::ParticleSolver() {
    const char *cl_kernel_src[] = {
        "typedef struct {\n",
        "    float3 pos;\n",
        "    float3 vel;\n",
        "} vertex_t;\n",
        "\n",
        "__kernel void vertex_step(__global vertex_t *in, __global vertex_t *out, const float dt) {\n",
        "    int id = get_global_id(0);\n",
        "\n",
        "    out[id].pos = in[id].pos + in[id].vel * dt;\n",
        "    out[id].vel = in[id].vel;\n",
        "}\n"
    };

    clGetPlatformIDs(100, &this->platform, NULL);
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &this->device, NULL);
    
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

    int err;
    this->context = clCreateContext(properties, 1, &this->device, NULL, NULL, &err);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "FUCK\n");
        exit(1);
    }
    this->queue = clCreateCommandQueue(context, this->device, 0, NULL);
    this->program = clCreateProgramWithSource(this->context, sizeof(cl_kernel_src)/sizeof(*cl_kernel_src), cl_kernel_src, NULL, NULL);

    err = clBuildProgram(this->program, 0, NULL, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buffer[10240];
        clGetProgramBuildInfo(this->program, this->device, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, NULL);
        fprintf(stderr, "CL Compilation failed:\n%s", buffer);
        exit(1);
    }

    this->kernel = clCreateKernel(this->program, "vertex_step", &err);
    if (!this->kernel || err != CL_SUCCESS) {
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

}