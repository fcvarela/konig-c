cmake_minimum_required (VERSION 2.8.8)

project(konig)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(KONIG_LIBRARY_NAME "konig")

set(KONIG_VERSION_MAJOR 0)
set(KONIG_VERSION_MINOR 1)

set(CMAKE_C_FLAGS "-Wall -pedantic -fPIC")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O2")

add_definitions(-DKONIG_VERSION="${KONIG_VERSION_MAJOR}.${KONIG_VERSION_MINOR}")

# Append the source files here
list (APPEND KONIG_SOURCES
  src/konig.cpp
  src/DrawableGraph.cpp
  src/GraphRenderer.cpp
  src/ParticleSolver.cpp
  src/clutils.cpp
)

# Append the header files here
list (APPEND KONIG_INCLUDE_FILES
  src/konig.h
)


# Create a shared lib
add_library (konig_core OBJECT ${KONIG_SOURCES})
add_library (${KONIG_LIBRARY_NAME} SHARED $<TARGET_OBJECTS:konig_core>)


# GLFW + GLEW Deps
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(OpenCL REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(GLEW REQUIRED glew)

include_directories(/usr/local/include/SOIL)
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${OPENCL_INCLUDE_DIR})

link_directories(/usr/local/lib)
link_directories(${GLEW_LIBRARY_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})
link_directories(${OPENGL_LIBRARIES})
link_directories(${OPENCL_LIBRARIES})

# Linking
target_link_libraries(${KONIG_LIBRARY_NAME} ${EXTRA_LIBS})
target_link_libraries(${KONIG_LIBRARY_NAME} ${GLEW_LIBRARY})
target_link_libraries(${KONIG_LIBRARY_NAME} ${GLFW_LIBRARIES})
target_link_libraries(${KONIG_LIBRARY_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${KONIG_LIBRARY_NAME} ${OPENCL_LIBRARIES})
target_link_libraries(${KONIG_LIBRARY_NAME} SOIL)

SET_TARGET_PROPERTIES(${KONIG_LIBRARY_NAME} PROPERTIES
                                            VERSION ${KONIG_VERSION_MAJOR}.${KONIG_VERSION_MINOR}
                                            SOVERSION ${KONIG_VERSION_MAJOR})

set(KONIG_LIB_INSTALL_DIR "")
if(DEFINED ENV{KONIG_LIB_ARCH})
  set(KONIG_LIB_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib/$ENV{KONIG_LIB_ARCH})
else()
  set(KONIG_LIB_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib)
endif()

INSTALL ( TARGETS ${KONIG_LIBRARY_NAME} DESTINATION ${KONIG_LIB_INSTALL_DIR})
INSTALL ( FILES ${KONIG_INCLUDE_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/lib${KONIG_LIBRARY_NAME})
