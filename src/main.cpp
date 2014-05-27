#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

#include "gfx/Renderer.h"
#include "gfx/VertexArray.h"
#include "gfx/shader/SimpleShader.h"

static void error_callback(int error, const char* description)
{
  fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}
int main(void) {
  glfwSetErrorCallback(error_callback);
  if (!glfwInit())
    exit(EXIT_FAILURE);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow* window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
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
    glfwSetKeyCallback(window, key_callback);
  }

  VertexArray vertexArray{{
    {0, 0.5f, 0},
    {0.5f, 0, 0},
    {0.5f, 0.5f, 0}
  }};
  vertexArray.flip();
  auto vArrayPtr = make_shared<VertexArray>(vertexArray);
  auto rObj1 = make_shared<RenderObject>(vArrayPtr);
  auto rObj2 = make_shared<RenderObject>(vArrayPtr);
  Renderer renderer;
  renderer.addObject(rObj1);
  renderer.addObject(rObj2);
  rObj2->translate({0.25f, 0.5f, 0});
  std::cout << "Use count : " << vArrayPtr.use_count() << std::endl;

  SimpleShader shader;
  shader();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    renderer.render();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
