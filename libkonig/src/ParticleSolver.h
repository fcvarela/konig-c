#ifndef KONIG_PARTICLE_SOLVER_H
#define KONIG_PARTICLE_SOLVER_H

#include <vector>
#include <stdint.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#if defined ( __APPLE__ ) || defined ( MACOSX )
    #define GLFW_EXPOSE_NATIVE_COCOA
    #define GLFW_EXPOSE_NATIVE_NSGL
    #include <OpenGL/OpenGL.h>
#elif defined ( WIN32 )
    #define GLFW_EXPOSE_NATIVE_WIN32
    #define GLFW_EXPOSE_NATIVE_WGL
#else
    #define GLFW_EXPOSE_NATIVE_X11
    #define GLFW_EXPOSE_NATIVE_GLX
#endif

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "Vertex.h"

namespace konig {

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

}

#endif
