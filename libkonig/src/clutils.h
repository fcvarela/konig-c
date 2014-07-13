
#include "gl.h"

const char * clutils__get_error_string(cl_int err);

cl_platform_id clutils__get_default_platform();
cl_device_id clutils__get_default_device(cl_platform_id platform);
cl_context clutils__make_context(cl_platform_id platform, cl_device_id device);
cl_command_queue clutils__make_command_queue(cl_context context, cl_device_id device);
cl_program clutils__load_program(cl_context context, cl_device_id device, const char *filename);
cl_kernel clutils__load_kernel(cl_program program, const char *kernel_name);
