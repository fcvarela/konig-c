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
        "    __global vertex_t *vertex = &in[id];\n",
        "    vertex->pos += vertex->vel * dt;\n",
        "}\n"
    };

    clGetPlatformIDs(100, &this->platform, NULL);
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &this->device, NULL);
    
    this->context = clCreateContext(NULL, 1, &this->device, NULL, NULL, NULL);
    this->queue = clCreateCommandQueue(context, this->device, 0, NULL);
    this->program = clCreateProgramWithSource(this->context, sizeof(cl_kernel_src)/sizeof(*cl_kernel_src), cl_kernel_src, NULL, NULL);

    int err = clBuildProgram(this->program, 0, NULL, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        char buffer[10240];
        clGetProgramBuildInfo(this->program, this->device, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, NULL);
        fprintf(stderr, "CL Compilation failed:\n%s", buffer);
        abort();
    }

    this->kernel = clCreateKernel(this->program, "vertex_step", &err);
    if (!this->kernel || err != CL_SUCCESS) {
        exit(1);
    }
}

ParticleSolver::~ParticleSolver() {}

void ParticleSolver::update(GLuint vbo_in, GLuint vbo_out) {
    this->cl_vbo_in = clCreateFromGLBuffer(this->context, CL_MEM_READ_ONLY, vbo_in, NULL);
    this->cl_vbo_out = clCreateFromGLBuffer(this->context, CL_MEM_READ_ONLY, vbo_out, NULL);
}

void ParticleSolver::prepare(GLuint vbo_in, GLuint vbo_out, size_t element_count) {
    clEnqueueAcquireGLObjects(this->queue, 1, &this->cl_vbo_in, 0, 0, 0);
    clEnqueueAcquireGLObjects(this->queue, 1, &this->cl_vbo_out, 0, 0, 0);

    // clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&this->cl_vbo);
    clEnqueueNDRangeKernel(queue, kernel, 2, NULL, &element_count, NULL, 0, 0, 0);
    clEnqueueReleaseGLObjects(queue, 1, &this->cl_vbo_in, 0, 0, 0);
    clEnqueueReleaseGLObjects(queue, 1, &this->cl_vbo_out, 0, 0, 0);
    clFinish(queue);
}

}