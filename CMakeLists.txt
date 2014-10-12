#TODO: Create find_package for glfw, glew, glm
cmake_minimum_required (VERSION 2.6)
project (glHondo)
find_package(OpenGL REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -static-libgcc -static-libstdc++")

SET(GLFW_BUILD_EXAMPLES OFF CACHE STRING "" FORCE)
SET(GLFW_BUILD_TESTS OFF CACHE STRING "" FORCE)
add_subdirectory(lib/glfw-3.0.4)

add_definitions(-DGLEW_STATIC)
set(GLEW_SOURCE lib/glew-1.10.0/src/glew.c)
set(GLEW_INCLUDE lib/glew-1.10.0/include)
add_library(GLEW_1100 STATIC
  ${GLEW_SOURCE}
  ${GLEW_INCLUDE}
)

set(SOIL_SOURCE lib/SOIL/src)
file(GLOB SOIL_SOURCES "${SOIL_SOURCE}/*.c")
file(GLOB SOIL_HEADERS "${SOIL_SOURCE}/*.h")
add_library(SOIL STATIC
  ${SOIL_SOURCES}
  ${SOIL_HEADERS}
)

set(BOOST_ROOT lib/boost_1_55_0)
find_package(Boost 1.55.0 REQUIRED)

MESSAGE("Boost information:") 
MESSAGE("  Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}") 
MESSAGE("  Boost_LIBRARIES: ${Boost_LIBRARIES}") 
MESSAGE("  Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}") 

include_directories (SYSTEM
  ${GLEW_INCLUDE}
  ${SOIL_SOURCE}
  lib/glm
  lib/glfw-3.0.4/include/GLFW/
  ${Boost_INCLUDE_DIRS}
)

#The order is important!
set(ALL_LIBS
  glfw
  GLEW_1100
  SOIL
  ${OPENGL_LIBRARY}
  ${GLFW_LIBRARIES}
  ${Boost_LIBRARIES}
)

file(GLOB_RECURSE GLHONDO_SOURCES "src/*.cpp")
file(GLOB_RECURSE GLHONDO_HEADERS "src/*.h")

set (GLHONDO_INCLUDE_DIRS "")
foreach (_headerFile ${GLHONDO_HEADERS})
  get_filename_component(_dir ${_headerFile} PATH)
  list (APPEND GLHONDO_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES GLHONDO_INCLUDE_DIRS)

include_directories(${GLHONDO_INCLUDE_DIRS})
add_executable (glHondo ${GLHONDO_SOURCES})
target_link_libraries(glHondo ${ALL_LIBS})
set_property(TARGET glHondo APPEND PROPERTY COMPILE_FLAGS "-g -Wall -Wextra -Wno-unused-parameter")
