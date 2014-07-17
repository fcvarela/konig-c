#include "clutils.h"
#include "ParticleSolver.h"

ParticleSolver::ParticleSolver() {
    platform = clutils__get_default_platform();
    device = clutils__get_default_device(platform);
    context = clutils__make_context(platform, device);
    queue = clutils__make_command_queue(context, device);

    program = clutils__load_program(context, device, "data/kernels/graphtopo.cl");
    vertices_kernel = clutils__load_kernel(program, "vertex_step");
    edges_kernel = clutils__load_kernel(program, "edge_step");
    sum_kernel = clutils__load_kernel(program, "integrate");
}

ParticleSolver::~ParticleSolver() {
    clReleaseKernel(vertices_kernel);
    clReleaseKernel(edges_kernel);
    clReleaseKernel(sum_kernel);
    clReleaseCommandQueue(queue);
    clReleaseProgram(program);
    clReleaseContext(context);
}

void ParticleSolver::step(GLuint vbo_in, GLuint vbo_out, GLuint edge_vbo, size_t vertex_element_count, size_t edge_element_count, float dt) {
    // solve vertex
    cl_vbo_in = clCreateFromGLBuffer(context, CL_MEM_READ_ONLY, vbo_in, NULL);
    cl_vbo_out = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, vbo_out, NULL);
    cl_edge_vbo = clCreateFromGLBuffer(context, CL_MEM_READ_ONLY, edge_vbo, NULL);

    clEnqueueAcquireGLObjects(queue, 1, &cl_vbo_in, 0, 0, 0);
    clEnqueueAcquireGLObjects(queue, 1, &cl_vbo_out, 0, 0, 0);
    clEnqueueAcquireGLObjects(queue, 1, &cl_edge_vbo, 0, 0, 0);

    // vertices
    clSetKernelArg(vertices_kernel, 0, sizeof(cl_mem), (void *)&cl_vbo_in);
    clSetKernelArg(vertices_kernel, 1, sizeof(cl_mem), (void *)&cl_vbo_out);
    cl_int status = clEnqueueNDRangeKernel(queue, vertices_kernel, 1, NULL, &vertex_element_count, NULL, 0, 0, 0);

    // edges
    clSetKernelArg(edges_kernel, 0, sizeof(cl_mem), (void *)&cl_edge_vbo);
    clSetKernelArg(edges_kernel, 1, sizeof(cl_mem), (void *)&cl_vbo_in);
    clSetKernelArg(edges_kernel, 2, sizeof(cl_mem), (void *)&cl_vbo_out);
    status = clEnqueueNDRangeKernel(queue, edges_kernel, 1, NULL, &edge_element_count, NULL, 0, 0, 0);

    // integrate
    clSetKernelArg(sum_kernel, 0, sizeof(cl_mem), (void *)&cl_vbo_in);
    clSetKernelArg(sum_kernel, 1, sizeof(cl_mem), (void *)&cl_vbo_out);
    clSetKernelArg(sum_kernel, 2, sizeof(float), &dt);
    status = clEnqueueNDRangeKernel(queue, sum_kernel, 1, NULL, &vertex_element_count, NULL, 0, 0, 0);

    clEnqueueReleaseGLObjects(queue, 1, &cl_vbo_in, 0, 0, 0);
    clEnqueueReleaseGLObjects(queue, 1, &cl_vbo_out, 0, 0, 0);
    clEnqueueReleaseGLObjects(queue, 1, &cl_edge_vbo, 0, 0, 0);
    clFlush(queue);
    clFinish(queue);
}
