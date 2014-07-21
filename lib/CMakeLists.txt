cmake_minimum_required (VERSION 2.6)

add_definitions(
  -DGLEW_STATIC
)

SET(GLFW_BUILD_EXAMPLES OFF CACHE STRING "" FORCE)
SET(GLFW_BUILD_TESTS OFF CACHE STRING "" FORCE)
add_subdirectory(glfw-3.0.4)

include_directories (
  glfw-3.0.4/include/GLFW/
  glew-1.10.0/include/
)

set(OPENGL_LIBRARY
  ${OPENGL_LIBRARY}
  ${CMAKE_DL_LIBS}
  ${GLFW_LIBRARIES}
)

set(GLEW_SOURCE
  glew-1.10.0/src/glew.c
)

set(GLEW_HEADERS
)

add_library(GLEW_1100 STATIC
  ${GLEW_SOURCE}
  ${GLEW_INCLUDE}
)

target_link_libraries(GLEW_1100
  ${OPENGL_LIBRARY}
  ${EXTRA_LIBS}
)

