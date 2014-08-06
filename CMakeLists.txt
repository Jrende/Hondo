cmake_minimum_required (VERSION 2.6)
project (glHondo)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_FLAGS "-std=c++1y -static-libgcc -static-libstdc++")

add_subdirectory(lib)

include_directories(SYSTEM
  lib/glfw-3.0.4/include/GLFW
  lib/glew-1.10.0/include/
  lib/glm
  lib/boost_1_55_0/
  lib/SOIL/src/
)

set(ALL_LIBS
  ${OPENGL_LIBRARY}
  ${Boost_LIBRARIES}
  GLEW_1100
  glfw
  SOIL
)

link_directories(
  lib/SOIL/lib
)

add_definitions(
  -DGLEW_STATIC
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
