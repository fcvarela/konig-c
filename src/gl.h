#ifndef KONIG_GL_H
#define KONIG_GL_H

#include <GL/glew.h>

#ifdef __APPLE__
#include "OpenCL/opencl.h"
#else
#include "CL/cl.h"
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

// for pure sequential memory (draw as vbo fast)
// aligned to 16 bytes for opencl null padding
typedef struct {
    cl_float pos[4];
    cl_float vel[4];
    cl_float acc[4];
    cl_float pad[4];
} vertex_t;

// for pure sequential memory (draw as vbo fast)
typedef struct {
    cl_uint vertex_idx1;
    cl_uint vertex_idx2;
    cl_uint pad1;
    cl_uint pad2;
} edge_t;

#endif
