cmake_minimum_required (VERSION 2.6)
project (glHondo)
set(CMAKE_CXX_FLAGS "-std=c++11")
add_executable(glHondo src/main.cpp)
add_subdirectory(lib/glfw-3.0.4)
include_directories(lib/glfw-3.0.4/include)
target_link_libraries(glHondo glfw ${GLFW_LIBRARIES})

install (TARGETS glHondo DESTINATION bin)
