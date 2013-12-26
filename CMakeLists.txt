# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.

project( Linear_cell_complex_load_off )

cmake_minimum_required(VERSION 2.6.2)
if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}" VERSION_GREATER 2.8.3)
  cmake_policy(VERSION 2.8.4)
else()
  cmake_policy(VERSION 2.6)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)

set(CGAL_SRC_FILES CGAL/assertions.cpp CGAL/io.cpp CGAL/Timer.cpp
                   CGAL/Real_timer.cpp CGAL/kernel.cpp CGAL/File_header_OFF.cpp
                   CGAL/File_header_extended_OFF.cpp CGAL/File_scanner_OFF.cpp
                   CGAL/io.cpp CGAL/File_writer_OFF.cpp)

# To use valgrind, we must disable rounding math ckeck.
# add_definition(-DCGAL_DISABLE_ROUNDING_MATH_CHECK)
# add_definition(-std=c++11)

include_directories(.)
include("CMakeLCCViewerQt.inc")

# Project classes
set(PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/MeshSimplification/edgeCollapse.hpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/MeshSimplification/edgeCollapse.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/MeshSimplification/edgeSelection.hpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/MeshSimplification/edgeSelection.cpp )

# In the next line, add all the source files.
add_executable(load_off load_off.cpp ${CGAL_SRC_FILES} ${PROJECT_SOURCES})
target_link_libraries(load_off ${MAP_VIEWER_LIBRARIES})

# for volume meshes
#add_executable(load_tetmesh load_tetmesh.cpp ${CGAL_SRC_FILES})
#target_link_libraries(load_tetmesh ${MAP_VIEWER_LIBRARIES})

