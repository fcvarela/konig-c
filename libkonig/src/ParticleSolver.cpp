#include "clutils.h"
#include "ParticleSolver.h"

ParticleSolver::ParticleSolver() {
    this->platform = clutils__get_default_platform();
    this->device = clutils__get_default_device(this->platform);
    this->context = clutils__make_context(this->platform, this->device);
    this->queue = clutils__make_command_queue(this->context, this->device);

    this->program = clutils__load_program(this->context, this->device, "data/kernels/graphtopo.cl");
    this->vertices_kernel = clutils__load_kernel(this->program, "vertex_step");
    this->edges_kernel = clutils__load_kernel(this->program, "edge_step");
    this->sum_kernel = clutils__load_kernel(this->program, "integrate");
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
