#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

#include <glm/glm.hpp>
#include "gfx/Renderer.h"
#include "gfx/VertexArray.h"
#include "gfx/shader/SimpleShader.h"
#include "input/Input.h"
#include "input/Action.h"
#include "gfx/ObjLoader.h"
#include <glm/gtx/string_cast.hpp>

static void error_callback(int error, const char* description)
{
  fputs(description, stderr);
}

auto camera = std::make_shared<Camera>();
float step = 0.01f;

void rotate_camera() {
  //std::cout << "rotate (" << Input::getMouseDX() << ", " << Input::getMouseDY() << ")" << std::endl;
  camera->rotate(-Input::get_mouse_dx() / 100.0f, camera->up);
  camera->rotate(-Input::get_mouse_dy() / 100.0f, glm::cross(camera->up, camera->dir));
}

const int width = 640;
const int height = 480;
int main(int argc, char ** argv) {
  glfwSetErrorCallback(error_callback);
  if (!glfwInit())
    exit(EXIT_FAILURE);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow* window = glfwCreateWindow(width, height, "Simple example", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
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

  Input::on(Action::Forward, []() {
    camera->move_forward(step);
  });

  Input::on(Action::Backward, []() {
    camera->move_forward(-step);
  });

  Input::on(Action::Left, []() {
    camera->move_right(-step);
  });

  Input::on(Action::Right, []() {
    camera->move_right(step);
  });

  Input::on(Action::Up, []() {
    camera->translate({0, -step, 0});
  });

  Input::on(Action::Down, []() {
    camera->translate({0, step, 0});
  });

  Input::on(Action::Down, []() {
    camera->translate({0, step, 0});
  });

  Input::on(Action::LockMouse, []() {
      Input::lock_mouse();
  });

  Input::on(Action::Test, []() {
  });

  ObjLoader loader("assets/Cube.obj");
  std::cout << loader.vertexCount << std::endl;
  auto vArrayPtr = std::shared_ptr<VertexArray>(new VertexArray(loader.getVertices(), loader.vertexCount, {3, 2, 3}));

  auto&& rObj1 = RenderObject(vArrayPtr);
  Renderer renderer(width, height);
  renderer.set_camera(camera);
  rObj1.translate({-0.5f, -0.5f, -1});
  rObj1.color = glm::vec3(1,0,0);
  renderer.add_object(rObj1);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  while (!glfwWindowShouldClose(window)) {
    Input::handle_input();
    glfwPollEvents();
    rotate_camera();

    renderer.render();
    glfwSwapBuffers(window);

    Input::reset_delta();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
