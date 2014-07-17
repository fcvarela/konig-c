cmake_minimum_required (VERSION 2.8.8)

project(konigapp)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_C_FLAGS "-Wall -pedantic -fPIC")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O2")

# Append the source files here
list (APPEND konigapp_SOURCES
  src/konigapp.c
)

add_executable(konigapp ${konigapp_SOURCES})

# GLFW + GLEW Deps
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(OpenCL REQUIRED)
find_package(Protobuf REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(GLEW REQUIRED glew)

include_directories(/usr/local/include)
include_directories(/usr/local/include/SOIL)

include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${OPENCL_INCLUDE_DIR})
include_directories(${PROTOBUF_INCLUDE_DIR})

link_directories(/usr/local/lib)
link_directories(/usr/local/lib/libkonig)
link_directories(${GLFW_LIBRARY_DIRS})
link_directories(${GLEW_LIBRARIES})
link_directories(${OPENGL_LIBRARIES})
link_directories(${OPENCL_LIBRARIES})
link_directories(${PROTOBUF_LIBRARIES})

# Linking
target_link_libraries(konigapp ${GLFW_LIBRARIES})
target_link_libraries(konigapp ${OPENGL_LIBRARIES})
target_link_libraries(konigapp ${OPENCL_LIBRARIES})
target_link_libraries(konigapp SOIL)
target_link_libraries(konigapp konig)
target_link_libraries(konigapp ${GLEW_LIBRARIES})
target_link_libraries(konigapp ${PROTOBUF_LIBRARIES})

