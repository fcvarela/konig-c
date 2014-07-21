cmake_minimum_required (VERSION 2.8.8)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(APP_NAME "konig")
set(CMAKE_C_FLAGS "-Wall -pedantic -fPIC")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O2")

# Append the source files here
list (APPEND KONIG_SOURCES
  src/konig.cpp
  src/DrawableGraph.cpp
  src/GraphRenderer.cpp
  src/ParticleSolver.cpp
  src/clutils.cpp
  src/Texture.cpp
  src/GraphRPCService.cpp
  src/graphproto.pb.cc
  src/konigapp.c
)

add_executable(${APP_NAME} ${KONIG_SOURCES})

# GLFW + GLEW Deps
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(OpenCL REQUIRED)
find_package(Protobuf REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(GLEW REQUIRED glew)

include_directories(/usr/local/include/SOIL)
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${OPENCL_INCLUDE_DIR})
include_directories(${PROTOBUF_INCLUDE_DIR})

link_directories(/usr/local/lib)
link_directories(${GLFW_LIBRARY_DIRS})
link_directories(${GLEW_LIBRARIES})
link_directories(${OPENGL_LIBRARIES})
link_directories(${OPENCL_LIBRARIES})
link_directories(${PROTOBUF_LIBRARIES})

# Linking
target_link_libraries(${APP_NAME} ${EXTRA_LIBS})
target_link_libraries(${APP_NAME} ${GLFW_LIBRARIES})
target_link_libraries(${APP_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${APP_NAME} ${OPENCL_LIBRARIES})
target_link_libraries(${APP_NAME} SOIL)
target_link_libraries(${APP_NAME} ${GLEW_LIBRARIES})
target_link_libraries(${APP_NAME} ${PROTOBUF_LIBRARIES})
