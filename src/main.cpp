#define GLM_FORCE_RADIANS
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

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
    glfwSetKeyCallback(window, Input::key_callback);
  }
  VertexArray&& vertexArray{{
    {0, 0.5f, 0},
    {0.5f, 0, 0},
    {0.5f, 0.5f, 0}
  }};

  Input::on(Action::Forward, []() {
    camera->translate({0, 0, -step});
  });
  Input::on(Action::Backward, []() {
    camera->translate({0, 0, step});
  });
  Input::on(Action::Left, []() {
    camera->translate({-step, 0, 0});
  });
  Input::on(Action::Right, []() {
    camera->translate({step, 0, 0});
  });
  Input::on(Action::Up, []() {
    camera->translate({0, -step, 0});
  });
  Input::on(Action::Down, []() {
    camera->translate({0, step, 0});
  });

  vertexArray.flip();
  auto vArrayPtr = std::make_shared<VertexArray>(vertexArray);
  auto rObj1 = std::make_shared<RenderObject>(vArrayPtr);
  auto rObj2 = std::make_shared<RenderObject>(vArrayPtr);
  Renderer renderer(width, height);
  renderer.addObject(rObj1);
  renderer.addObject(rObj2);
  renderer.setCamera(camera);
  auto vec = glm::vec3({1,2,3});
  rObj1->translate(vec);
  rObj2->translate({0.25f, 0.5f, 5});
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    Input::handleInput();
    glClear(GL_COLOR_BUFFER_BIT);
    renderer.render();
    glfwSwapBuffers(window);
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
