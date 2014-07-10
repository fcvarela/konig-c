#ifndef KONIG_PARTICLE_SOLVER_H
#define KONIG_PARTICLE_SOLVER_H

#include <vector>
#include <stdint.h>

#include "gl.h"

class ParticleSolver {
public:
    cl_platform_id platform;
    cl_device_id device;
    cl_context context;
    cl_command_queue queue;
    cl_program program;

    cl_kernel vertices_kernel;
    cl_kernel edges_kernel;
    cl_kernel sum_kernel;

    cl_mem cl_vbo_in, cl_vbo_out, cl_edge_vbo;

    ParticleSolver();
    ~ParticleSolver();

    void pick_device();
    void init_context();
    void load_kernel();

    void step(GLuint vbo_in, GLuint vbo_out, GLuint edge_vbo, size_t vertex_element_count, size_t edge_element_count, float dt);
};

#endif
