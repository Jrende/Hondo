#define GLM_FORCE_RADIANS
#define PI 3.14159265358979
#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gfx/Renderer.hpp"
#include "gfx/VertexArray.hpp"
#include "gfx/importer/ObjLoader.hpp"
#include "gfx/lights/Light.hpp"
#include "gfx/lights/PointLight.hpp"
#include "gfx/shader/SimpleShader.hpp"

#include "input/Actions.hpp"
#include "input/Input.hpp"
#include "DebugUtils.h"

static void error_callback(int error, const char* description)
{
  fputs(description, stderr);
}

auto camera = std::make_shared<Camera>();
float step = 0.01f;

void rotate_camera() {
  camera->rotate(-Input::get_mouse_dx() / 100.0f, camera->up);
  camera->rotate(-Input::get_mouse_dy() / 100.0f, glm::cross(camera->up, camera->dir));
}

float randx() {
  return (float) (rand() % 100)/100;
}
const int width = 1024;
const int height = 768;
int main(int argc, char ** argv) {
  glfwSetErrorCallback(error_callback);
  if (!glfwInit())
    exit(EXIT_FAILURE);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow* window = glfwCreateWindow(width, height, "glHondo", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  //To discard error 1280 from glewInit().
  glGetError();
  if(GLEW_OK != err) {
    std::cout << glewGetErrorString(err) << std::endl;
  }

  {
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    printf("Renderer: %s\n", renderer);
    printf("Version: %s\n", version);
    glfwSetCursorPosCallback(window, Input::cursor_pos_callback);
    glfwSetKeyCallback(window, Input::key_callback);
    Input::set_active_window(window);
  }
  Renderer renderer(width, height);

  Input::on(Actions::Forward, []() {
    camera->move_forward(step);
  });

  Input::on(Actions::Backward, []() {
    camera->move_forward(-step);
  });

  Input::on(Actions::Left, []() {
    camera->move_right(-step);
  });

  Input::on(Actions::Right, []() {
    camera->move_right(step);
  });

  Input::on(Actions::Up, []() {
    camera->translate({0, step, 0});
  });

  Input::on(Actions::Down, []() {
    camera->translate({0, -step, 0});
  });

  Input::on(GLFW_KEY_Z, [&] {
      renderer.toggle_wireframe();
  });

  Input::on(GLFW_KEY_G, []() {
      Input::lock_mouse();
  });
  ObjLoader loader;
  loader.preload("assets/Cube.obj");
  loader.preload("assets/Floor.obj");
  loader.load_preloaded_data();
  auto vArrayPtr = std::shared_ptr<VertexArray>(new VertexArray(loader.vertex_array, loader.index_array, loader.vertex_count, {3, 2, 3}));

  for(int i = -5; i < 5; i++) {
    for(int j = -5; j < 5; j++) {
      if((i % 2 == 0) || (j % 2 == 0)) {
	const auto& cube = std::shared_ptr<RenderObject>(new RenderObject(vArrayPtr, loader.mesh_list[0]));
	cube->translate({i*4.0f, 1.01f, j*4.0f});
	renderer.add_object(cube);
      }
      const auto& floor = std::shared_ptr<RenderObject>(new RenderObject(vArrayPtr, loader.mesh_list[1]));
      floor->translate({i*4.0f, 0, j*4.0f});
      floor->scale({2, 2, 2});
      renderer.add_object(floor);
    }
  }

  /*
  const auto& cube = std::shared_ptr<RenderObject>(new RenderObject(vArrayPtr, loader.mesh_list[0]));
  cube->translate({0, 1.01, 0});
  renderer.add_object(cube);

  const auto& floor = std::shared_ptr<RenderObject>(new RenderObject(vArrayPtr, loader.mesh_list[1]));
  floor->scale({10, 1, 10});
  renderer.add_object(floor);
  */

  renderer.set_camera(camera);
  auto pl = std::shared_ptr<PointLight>(new PointLight({0,2,0}, {1,1,1}));
  renderer.add_light(pl);

  Input::on(GLFW_KEY_I, [&] {
      pl->translate({ 0.01f, 0, 0});
  }, true);
  Input::on(GLFW_KEY_K, [&] {
      pl->translate({-0.01f, 0, 0});
  }, true);
  Input::on(GLFW_KEY_J, [&] {
      pl->translate({0, 0,  0.01f});
  }, true);
  Input::on(GLFW_KEY_L, [&] {
      pl->translate({0, 0, -0.01f});
  }, true);
  Input::on(GLFW_KEY_O, [&] {
      pl->translate({0,  0.01f, 0});
  }, true);
  Input::on(GLFW_KEY_U, [&] {
      pl->translate({0,-0.01f, 0});
  }, true);

  const int radius = 2;
  float i = 0;
  camera->translate({0, 2, 0});
  while (!glfwWindowShouldClose(window)) {
    Input::handle_input();
    glfwPollEvents();
    rotate_camera();

    renderer.render();
    renderer.draw_point(pl->pos);
    renderer.draw_line({0, 0, 0}, {0, 1, 0});

    glfwSwapBuffers(window);

    Input::reset_delta();
    if(i > 360) {
       i=0;
    }
    i += 0.1f;

    calcFPS(window, 1.0, "Current FPS: ");
    checkForGlError();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}

