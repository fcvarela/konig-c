cmake_minimum_required (VERSION 2.8.8)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(APP_NAME "konig")
set(CMAKE_C_FLAGS "-Wall -pedantic -fPIC")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O2")

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})

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

# PKG-CONFIG
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

find_package(OpenGL REQUIRED)
find_package(OpenCL REQUIRED)

find_package(Protobuf REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW REQUIRED)
find_package(ANTTWEAKBAR REQUIRED)

# Headers
include_directories(/usr/local/include/SOIL)
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${OPENCL_INCLUDE_DIRS})
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${ANT_TWEAK_BAR_INCLUDE_PATH})

# Xcode bug workaround
set(CMAKE_SHARED_LINKER_FLAGS "-L${GLFW_LIBRARY_DIRS}")
set(CMAKE_EXE_LINKER_FLAGS "-L${GLFW_LIBRARY_DIRS}")
set(CMAKE_LINKER_LINKER_FLAGS "-L${GLFW_LIBRARY_DIRS}")

set(CMAKE_SHARED_LINKER_FLAGS "-L/usr/local/lib")
set(CMAKE_EXE_LINKER_FLAGS "-L/usr/local/lib")
set(CMAKE_LINKER_LINKER_FLAGS "-L/usr/local/lib")

add_executable(${APP_NAME} ${KONIG_SOURCES})

# Linking
target_link_libraries(${APP_NAME} ${GLFW_LIBRARIES})
target_link_libraries(${APP_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${APP_NAME} ${OPENCL_LIBRARIES})
target_link_libraries(${APP_NAME} SOIL)
target_link_libraries(${APP_NAME} ${GLEW_LIBRARIES})
target_link_libraries(${APP_NAME} ${PROTOBUF_LIBRARIES})
target_link_libraries(${APP_NAME} ${ANT_TWEAK_BAR_LIBRARY})

