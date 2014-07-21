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

#include <SOIL.h>

// for pure sequential memory (draw as vbo fast)
// aligned to 16 bytes for opencl null padding
typedef struct {
    float pos[4];
    float vel[4];
    float acc[4];
} vertex_t;

// for pure sequential memory (draw as vbo fast)
typedef struct {
    uint32_t vertex_idx1;
    uint32_t vertex_idx2;
} edge_t;

#endif
