cmake_minimum_required (VERSION 2.8.8)

project(konig)

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
  src/Graph.cpp
  )

# Append the header files here
list (APPEND KONIG_INCLUDE_FILES
  src/konig.h
  )

# Create a shared lib
add_library (konig_core OBJECT ${KONIG_SOURCES})
add_library (${KONIG_LIBRARY_NAME} SHARED $<TARGET_OBJECTS:konig_core>)

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

