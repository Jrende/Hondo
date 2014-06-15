#define GLM_FORCE_RADIANS
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

#include <glm/glm.hpp>
#include "gfx/Renderer.h"
#include "gfx/VertexArray.h"
#include "gfx/shader/SimpleShader.h"
#include "input/Input.h"
#include "input/Action.h"

static void error_callback(int error, const char* description)
{
  fputs(description, stderr);
}

auto camera = std::make_shared<Camera>();
float step = 0.01f;

void rotateCamera() {
  //std::cout << "rotate (" << Input::getMouseDX() << ", " << Input::getMouseDY() << ")" << std::endl;
  camera->rotate(Input::getMouseDX() / 100.0f, {0, 1, 0});
  camera->rotate(Input::getMouseDY() / 100.0f, {1, 0, 0});
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
    Input::setActiveWindow(window);
  }

  auto vArrayPtr = std::shared_ptr<VertexArray>(new VertexArray{{
      {0, 0.5f, 0},
      {0.5f, 0, 0},
      {0.5f, 0.5f, 0}
      }});
  vArrayPtr->flip();

  Input::on(Action::Forward, []() {
    camera->move_forward(step);
  });

  Input::on(Action::Backward, []() {
    camera->move_forward(-step);
  });

  Input::on(Action::Left, []() {
    camera->move_right(step);
  });

  Input::on(Action::Right, []() {
    camera->move_right(-step);
  });

  Input::on(Action::Up, []() {
    camera->translate({0, -step, 0});
  });

  Input::on(Action::Down, []() {
    camera->translate({0, step, 0});
  });

  Input::on(Action::LockMouse, []() {
      Input::lockMouse();
  });

  auto rObj1 = std::make_shared<RenderObject>(vArrayPtr);
  auto rObj2 = std::make_shared<RenderObject>(vArrayPtr);
  Renderer renderer(width, height);
  renderer.addObject(rObj1);
  renderer.addObject(rObj2);
  renderer.setCamera(camera);
  rObj1->translate({0,0,3});
  rObj2->translate({0.25f, 0.5f, 5});
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  while (!glfwWindowShouldClose(window)) {
    Input::handleInput();
    glfwPollEvents();
    rotateCamera();

    glClear(GL_COLOR_BUFFER_BIT);
    renderer.render();
    glfwSwapBuffers(window);

    Input::resetDelta();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
