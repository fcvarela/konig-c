#include <stdlib.h>

#include "ParticleSolver.h"

namespace konig {

ParticleSolver::ParticleSolver() {
    const char *cl_kernel_src[] = {
        "typedef struct {\n",
        "    uint active;\n",
        "    float3 pos;\n",
        "    float3 vel;\n",
        "    float dummy;\n",
        "} vertex_t;\n",
        "\n",
        "__kernel void vertex_step(__global vertex_t *in, __global vertex_t *out, const float dt) {\n",
        "    int id = get_global_id(0);\n",
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
    clReleaseMemObject(this->cl_vbo_in);
    clReleaseMemObject(this->cl_vbo_in);
    clReleaseKernel(this->kernel);
    clReleaseProgram(program);
    clReleaseContext(context);
}

void ParticleSolver::step(GLuint vbo_in, GLuint vbo_out, size_t element_count, float dt) {
    glFinish();
    this->cl_vbo_in = clCreateFromGLBuffer(this->context, CL_MEM_READ_ONLY, vbo_in, NULL);
    this->cl_vbo_out = clCreateFromGLBuffer(this->context, CL_MEM_WRITE_ONLY, vbo_out, NULL);

    clEnqueueAcquireGLObjects(this->queue, 1, &this->cl_vbo_in, 0, 0, 0);
    clEnqueueAcquireGLObjects(this->queue, 1, &this->cl_vbo_out, 0, 0, 0);

    clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&this->cl_vbo_in);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&this->cl_vbo_out);
    clSetKernelArg(kernel, 2, sizeof(float), &dt);

    size_t global_work_size = 128;

    clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_work_size, NULL, 0, 0, 0);

    clEnqueueReleaseGLObjects(queue, 1, &this->cl_vbo_in, 0, 0, 0);
    clEnqueueReleaseGLObjects(queue, 1, &this->cl_vbo_out, 0, 0, 0);
    clFinish(queue);
}

}