#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <math.h>

#include <GL/glew.h>
#include <glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <SOIL.h>

#include "gfx/Renderer.hpp"
#include "gfx/importer/ObjLoader.hpp"
#include "gfx/VertexArray.hpp"
#include "gfx/shader/SimpleShader.hpp"
#include "input/Input.hpp"
#include "input/Actions.hpp"
#define PI 3.14159265358979

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
  GLFWwindow* window = glfwCreateWindow(width, height, "glHondo", NULL, NULL);
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
    camera->translate({0, -step, 0});
  });

  Input::on(Actions::Down, []() {
    camera->translate({0, step, 0});
  });

  Input::on(GLFW_KEY_Z, [&] {
      renderer.toggle_wireframe();
  });

  Input::on(GLFW_KEY_G, []() {
      Input::lock_mouse();
  });
  ObjLoader loader;
  //second cube should have start as 24, and length 36
  loader.preload("assets/SmoothCube.obj");
  loader.preload("assets/Cube2.obj");
  loader.load_preloaded_data();
  auto vArrayPtr = std::shared_ptr<VertexArray>(new VertexArray(loader.vertex_array, loader.index_array, loader.vertex_count, {3, 2, 3}));

  Input::on(GLFW_KEY_U, [&]() {
      vArrayPtr->add_start();
  });

  Input::on(GLFW_KEY_J, [&]() {
      vArrayPtr->sub_start();
  });

  Input::on(GLFW_KEY_I, [&]() {
      vArrayPtr->add_end();
  });

  Input::on(GLFW_KEY_K, [&]() {
      vArrayPtr->sub_end();
  });

  /*
  int a,b,c;
  a = b = c = 30;
  std::cout << "Lets draw " << a*b*c << " cubes!" << std::endl;
  for(int i = 0; i < a; i++) {
    for(int j = 0; j < b; j++) {
      for(int k = 0; k < c; k++) {
	auto&& rObj1 = RenderObject(vArrayPtr, loader.mesh_list[0]);
	rObj1.translate({i*3.0f, j*3.0f, k*3.0f});
	rObj1.color = {1, 1, 1};
	renderer.add_object(rObj1);
      }
    }
  }
  */
  auto rObj1 = std::shared_ptr<RenderObject>(new RenderObject(vArrayPtr, loader.mesh_list[0]));
  rObj1->translate({4, 0, 0});
  rObj1->color = {1, 1, 1};
  renderer.add_object(rObj1);

  auto rObj2 = std::shared_ptr<RenderObject>(new RenderObject(vArrayPtr, loader.mesh_list[1]));
  rObj2->translate({0, 0, 0});
  rObj2->color = {1, 1, 1};
  renderer.add_object(rObj2);

  renderer.set_camera(camera);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  const int radius = 2;
  float i = 0;
  while (!glfwWindowShouldClose(window)) {
    Input::handle_input();
    glfwPollEvents();
    rotate_camera();

    renderer.render();
    rObj1->set_position({sin(i * (PI/180)) * radius, 0, cos(i * (PI/180)) * radius});
    glfwSwapBuffers(window);

    Input::reset_delta();
    if(i > 360) {
       i=0;
    }
    i += 0.1f;
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
