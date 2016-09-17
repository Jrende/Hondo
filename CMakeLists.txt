#TODO: Create find_package for glfw, glew, glm
cmake_minimum_required (VERSION 2.6)
project (Hondo)
find_package(OpenGL REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -static-libgcc -static-libstdc++")

SET(GLFW_BUILD_EXAMPLES OFF CACHE STRING "" FORCE)
SET(GLFW_BUILD_TESTS OFF CACHE STRING "" FORCE)

add_subdirectory(lib/glfw)

#add_definitions(-DGLEW_STATIC)
set(GLEW_SOURCE lib/glew-1.10.0/src/glew.c)
set(GLEW_INCLUDE lib/glew-1.10.0/include)
MESSAGE("GLEW_HEADERS: ${GLEW_HEADERS}")
add_library(GLEW_1100 SHARED
  ${GLEW_SOURCE}
)
target_link_libraries(GLEW_1100
  ${OPENGL_LIBRARY}
)

set(SOIL_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/SOIL)
file(GLOB SOIL_SOURCES "${SOIL_SOURCE_DIR}/*.c")
add_library(SOIL SHARED
  ${SOIL_SOURCES}
)
target_link_libraries(SOIL
  GLEW_1100
  ${OPENGL_LIBRARY}
)

set(BOOST_ROOT lib/boost_1_60_0)
find_package(Boost 1.60.0 REQUIRED)

MESSAGE("Boost information:")
MESSAGE("  Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
MESSAGE("  Boost_LIBRARIES: ${Boost_LIBRARIES}")
MESSAGE("  Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")

add_library(nanovg
  lib/nanovg/src/nanovg.c
)

include_directories (SYSTEM
  ${GLEW_INCLUDE}
  ${SOIL_SOURCE_DIR}
  lib/glm
  lib/glfw/include
  ${Boost_INCLUDE_DIRS}
  lib/nanovg/src
)

MESSAGE("GLFW_LIBS: ${GLFW_LIBRARIES}")
#The order is important!
set(ALL_LIBS
  glfw
  GLEW_1100
  SOIL
  ${OPENGL_gl_LIBRARY}
  ${OPENGL_glu_LIBRARY}
  ${GLFW_LIBRARIES}
  Xcursor
  Xinerama
  Xi
  ${Boost_LIBRARIES}
  nanovg
)

file(GLOB_RECURSE HONDO_SOURCES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.cpp")
file(GLOB_RECURSE HONDO_HEADERS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.h")

set (HONDO_INCLUDE_DIRS "")
foreach (_headerFile ${HONDO_HEADERS})
  get_filename_component(_dir ${_headerFile} PATH)
  list (APPEND HONDO_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES HONDO_INCLUDE_DIRS)

list(REMOVE_ITEM HONDO_SOURCES "src/OctreeTest.cpp")
list(REMOVE_ITEM HONDO_SOURCES "src/main.cpp")

MESSAGE("sources: ${HONDO_SOURCES}")

include_directories(${HONDO_INCLUDE_DIRS})

add_executable (Hondo ${HONDO_SOURCES} "src/main.cpp")
target_link_libraries(Hondo ${ALL_LIBS})
set_property(TARGET Hondo APPEND PROPERTY COMPILE_FLAGS "-g -Wall -Wextra -Wno-unused-parameter")

add_executable (OctreeTest ${HONDO_SOURCES} "src/OctreeTest.cpp")
target_link_libraries(OctreeTest ${ALL_LIBS})
set_property(TARGET OctreeTest APPEND PROPERTY COMPILE_FLAGS "-g -Wall -Wextra -Wno-unused-parameter")
