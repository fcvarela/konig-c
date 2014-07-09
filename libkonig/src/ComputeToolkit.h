#ifndef KONIG_COMPUTE_TOOKIT_H
#define KONIG_COMPUTE_TOOKIT_H

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

namespace konig {

class ComputeToolkit {

};

}

#endif
