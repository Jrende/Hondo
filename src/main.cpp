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
#include "gfx/SkyBox.hpp"
#include "gfx/importer/ObjLoader.hpp"
#include "gfx/lights/Light.hpp"
#include "gfx/lights/PointLight.hpp"
#include "gfx/lights/DirLight.hpp"
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
int selected_light = -1;

static void scroll_callback(GLFWwindow* window, double x_offset, double y_offset) {
  step = fmax(0.01f, fmin(step * pow(1.5, y_offset), 5));
}

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
    glfwSetScrollCallback(window, scroll_callback);
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
  loader.preload_file("assets/sponza.obj");
  loader.preload_file("assets/SkyDome16.obj");
  std::cout << "Load files\n";
  loader.load_files();
  std::cout << "Loading files done\n";
  Mesh skydome_mesh = loader.get_meshes("assets/SkyDome16.obj")[0];
  std::vector<Mesh> sponza_meshes = loader.get_meshes("assets/sponza.obj");

  auto pl2 = std::make_shared<DirLight>(glm::vec3{-1, -1, -1}, glm::vec3{1, 1, 1});
  pl2->ambient_intensity = 0.1f;
  renderer.add_light(pl2);

  for(auto& sponza_mesh: sponza_meshes) {
    auto mesh = std::make_shared<RenderObject>(sponza_mesh);
    mesh->scale({0.01, 0.01, 0.01});
    renderer.add_object(mesh);
  }

  for(int i = -5; i < 5; i++) {
    for(int j = -5; j < 5; j++) {
      if((i % 3 == 0) && (j % 3 == 0)) {
	auto r = ((rand() % 100)/100.0); auto g = ((rand() % 100)/100.0); auto b = ((rand() % 100)/100.0);
	auto pl2 = std::make_shared<PointLight>(glm::vec3{i * 4, 2.1, j * 4}, glm::vec3{r, g, b});
	pl2->ambient_intensity = 0;
	renderer.add_light(pl2);
      }
    }
  }

  std::shared_ptr<SkyBox> sky = std::make_shared<SkyBox>(camera, skydome_mesh);
  renderer.set_skybox(sky);

  Input::on(GLFW_KEY_I, [&] {
      renderer.get_shown_light()->translate({ 0.01f, 0, 0});
  }, true);
  Input::on(GLFW_KEY_K, [&] {
      renderer.get_shown_light()->translate({-0.01f, 0, 0});
  }, true);
  Input::on(GLFW_KEY_J, [&] {
      renderer.get_shown_light()->translate({0, 0,  0.01f});
  }, true);
  Input::on(GLFW_KEY_L, [&] {
      renderer.get_shown_light()->translate({0, 0, -0.01f});
  }, true);
  Input::on(GLFW_KEY_O, [&] {
      renderer.get_shown_light()->translate({0,  0.01f, 0});
  }, true);

  Input::on(GLFW_KEY_U, [&] {
      renderer.get_shown_light()->translate({0,-0.01f, 0});
  }, true);

  Input::on(GLFW_KEY_PAGE_UP, [&] {
      if(selected_light < renderer.light_count()) {
	renderer.show_single_light(++selected_light);
      }
  }, false);
  Input::on(GLFW_KEY_PAGE_DOWN, [&] {
      if(selected_light > 0) {
	renderer.show_single_light(--selected_light);
      }
  }, false);
  Input::on(GLFW_KEY_RIGHT_CONTROL, [&] {
	renderer.show_single_light(-1);
  }, false);

  float i = 0;
  camera.translate({0, 2, 0});
  while (!glfwWindowShouldClose(window)) {
    Input::handle_input();
    glfwPollEvents();
    rotate_camera(camera);
    renderer.pre_render();

    renderer.render();
    draw_rain(&renderer);

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

