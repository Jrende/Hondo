#define GLM_FORCE_RADIANS
#define PI 3.14159265358979
#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
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

std::vector<std::pair<glm::vec3, glm::vec3>> rain;
void draw_rain(Renderer* r) {
  static float speed = 0.5;
  //if((rand() % 100)/100.0 < 0.5) {
  //for(int i = 0; i < 5; i++) {
  {
    auto x = ((rand() % 100)/100.0) * 10.0f;
    auto y = 20;
    auto z = ((rand() % 100)/100.0) * 10.0f;
    glm::vec3 from = glm::vec3(x,y,z);
    glm::vec3 to = from + glm::vec3{5, -16, 5};
    rain.push_back(std::make_pair(from, to));
  }
  std::vector<std::pair<glm::vec3, glm::vec3>> new_rain;
  for(auto& rain_pos: rain) {
    auto& from = std::get<0>(rain_pos);
    auto& to = std::get<1>(rain_pos);
    auto dir = glm::normalize(to - from);
    from += dir * speed;
    to += dir * speed;
    if(from.y > 0) {
      new_rain.push_back(rain_pos);
    }
  }
  r->draw_lines(rain, {0.1, 0.1, 0.1});
  rain = new_rain;
}

static void error_callback(int error, const char* description)
{
  fputs(description, stderr);
}

float step = 0.01f;

void rotate_camera(Camera& camera) {
  camera.rotate(-Input::get_mouse_dx() / 100.0f, camera.up);
  camera.rotate(-Input::get_mouse_dy() / 100.0f, glm::cross(camera.up, camera.dir));
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
  auto& camera = renderer.get_camera();

  Input::on(Actions::Forward, [&]() {
    camera.move_forward(step);
  });

  Input::on(Actions::Backward, [&]() {
    camera.move_forward(-step);
  });

  Input::on(Actions::Left, [&]() {
    camera.move_right(-step);
  });

  Input::on(Actions::Right, [&]() {
    camera.move_right(step);
  });

  Input::on(Actions::Up, [&]() {
    camera.translate({0, step, 0});
  });

  Input::on(Actions::Down, [&]() {
    camera.translate({0, -step, 0});
  });

  Input::on(GLFW_KEY_Z, [&] {
      renderer.toggle_wireframe();
  });

  Input::on(GLFW_KEY_G, []() {
      Input::lock_mouse();
  });
  ObjLoader loader;
  loader.preload("assets/Cube.obj");
  //loader.preload("assets/Floor.obj");
  loader.load_preloaded_data();

  /*
  for(int i = -5; i < 5; i++) {
    for(int j = -5; j < 5; j++) {
      if((i % 2 == 0) || (j % 2 == 0)) {
	auto cube = RenderObject(vArrayPtr, loader.mesh_list[0]);
	cube.translate({i*4.0f, 1.01f, j*4.0f});
	renderer.add_object(cube);
      }
      auto floor = RenderObject(vArrayPtr, loader.mesh_list[1]);
      floor.translate({i*4.0f, 0, j*4.0f});
      floor.scale({2, 2, 2});
      renderer.add_object(floor);
    }
  }

  auto cube = RenderObject(vArrayPtr, loader.mesh_list[0]);
  cube.translate({0, 1.01, 0});
  renderer.add_object(cube);

  auto floor = RenderObject(vArrayPtr, loader.mesh_list[1]);
  floor.scale({10, 1, 10});
  renderer.add_object(floor);
  */
  const auto& vArrayPtr = VertexArray{loader.vertex_array, loader.index_array, loader.vertex_count, {3, 2, 3, 3, 3}};

  auto cube = std::make_shared<RenderObject>(vArrayPtr, loader.mesh_list[0]);
  //cube->translate({0, 1.01, 0});
  renderer.add_object(cube);

  /*
  auto cube2 = RenderObject{vArrayPtr, loader.mesh_list[0]};
  cube2.translate({0, 1.01, 0});
  renderer.add_object(cube2);
  */



  /*
  auto pl1 = std::make_shared<PointLight>(glm::vec3{0, 2.1, 0}, glm::vec3{1, 1, 1});
  renderer.add_light(pl1);
  */

  auto pl1 = std::make_shared<Light>(glm::vec3{1, 1, 1}, glm::vec3{1, 1, 1});
  renderer.add_light(pl1);

  /*
  auto pl2 = std::make_shared<PointLight>(glm::vec3{0, 2.1, 0}, glm::vec3{0, 1, 0});
  renderer.add_light(pl2);

  auto pl3 = std::make_shared<PointLight>(glm::vec3{0, 2.1, 0}, glm::vec3{0, 0, 1});
  renderer.add_light(pl3);
  */

  Input::on(GLFW_KEY_I, [&] {
      pl1->translate({ 0.01f, 0, 0});
  }, true);
  Input::on(GLFW_KEY_K, [&] {
      pl1->translate({-0.01f, 0, 0});
  }, true);
  Input::on(GLFW_KEY_J, [&] {
      pl1->translate({0, 0,  0.01f});
  }, true);
  Input::on(GLFW_KEY_L, [&] {
      pl1->translate({0, 0, -0.01f});
  }, true);
  Input::on(GLFW_KEY_O, [&] {
      pl1->translate({0,  0.01f, 0});
  }, true);
  Input::on(GLFW_KEY_U, [&] {
      pl1->translate({0,-0.01f, 0});
  }, true);

  std::vector<glm::vec3> positions;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec3> tangents;
  std::vector<glm::vec3> bitangents;
  const auto& va = loader.vertex_array;
  int size = loader.vertex_array.size() / 14;
  std::cout << "size: " << size << std::endl;
  for(auto i = 0; i < loader.vertex_array.size(); i+=14) {
    positions.push_back({va[i + 0], va[i + 1], va[i + 2]});
    normals.push_back({va[i + 5], va[i + 6], va[i + 7]});
    tangents.push_back({va[i + 8], va[i + 9], va[i + 10]});
    bitangents.push_back({va[i + 11], va[i + 12], va[i + 13]});
  }

  float i = 0;
  camera.translate({0, 2, 0});
  while (!glfwWindowShouldClose(window)) {
    Input::handle_input();
    glfwPollEvents();
    rotate_camera(camera);
    renderer.pre_render();

    renderer.render();
    draw_rain(&renderer);

    renderer.draw_point(pl1->pos);

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
  return 0;
}

