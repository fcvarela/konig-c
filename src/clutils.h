#ifdef __APPLE__
#include "OpenCL/opencl.h"
#else
#include "CL/cl.h"
#endif

namespace konig {
const char * get_error_string(cl_int err);
}
