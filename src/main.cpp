#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <nanovg.h>
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg_gl.h>

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

void myCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *msg, void *data) {
  std::cout <<  "debug call: " << msg << std::endl;
}

glm::vec3 get_random_color() {
  auto r = ((rand() % 100)/100.0);
  auto g = ((rand() % 100)/100.0);
  auto b = ((rand() % 100)/100.0);
  return glm::normalize(glm::vec3{r, g, b});
}

glm::vec3 pos;
glm::vec3 scale;
std::vector<std::pair<glm::vec3, glm::vec3>> rain;
void draw_rain(Renderer* r) {
  static float speed = 0.75;
  //if((rand() % 100)/100.0 < 0.5) {
  //for(int i = 0; i < 5; i++) {
  {
    auto x = ((rand() % 100)/100.0) * -34 + 14;
    auto y = 22 + pos.y;
    auto z = ((rand() % 100)/100.0) * -10 + 3.1;
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

double target_x = 0;
double target_y = 0;
double current_x = 0;
double current_y = 0;
double MOUSE_X_SENSITIVITY = 20;
double MOUSE_Y_SENSITIVITY = 20;
double PANNING_SPEED = 15;
void rotate_camera(Camera& camera) {
  const auto x = Input::get_mouse_dx() / MOUSE_X_SENSITIVITY;
  const auto y = Input::get_mouse_dy() / MOUSE_Y_SENSITIVITY;
  target_x += x;
  target_y += y;
  auto dx = (target_x - current_x) / PANNING_SPEED;
  auto dy = (target_y - current_y) / PANNING_SPEED;
  if(fabs(dx) < 0.001 && fabs(dy) < 0.001) {
    return;
  }
  current_x += dx + copysign(0.01, dx);
  current_y += dy + copysign(0.01, dy);
  camera.rotate(-dx, camera.up);
  camera.rotate(dy, glm::cross(camera.up, camera.dir));
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
  glfwWindowHint( GLFW_OPENGL_DEBUG_CONTEXT, true );
  GLFWwindow* window = glfwCreateWindow(width, height, "Hondo", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  //To discard error 1280 from glewInit().
  glGetError();
  if(GLEW_OK != err)
    std::cout << glewGetErrorString(err) << std::endl;

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

  struct NVGcontext* vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_DEBUG);
  //glDebugMessageCallback( myCallback, NULL );
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
  loader.preload_file("assets/sponza-minus.obj");
  //loader.preload_file("assets/SmoothCube.obj");
  //loader.preload_file("assets/sphere.obj");
  //loader.preload_file("assets/Floor.obj");
  loader.preload_file("assets/SkyDome16.obj");
  std::cout << "Load files\n";
  loader.load_files();
  std::cout << "Loading files done\n";
  Mesh skydome_mesh = loader.get_meshes("assets/SkyDome16.obj")[0];
  //Mesh cube_mesh = loader.get_meshes("assets/SmoothCube.obj")[0];
  //Mesh sphere_mesh = loader.get_meshes("assets/sphere.obj")[0];
  //Mesh floor_mesh = loader.get_meshes("assets/Floor.obj")[0];
  std::vector<Mesh> sponza_meshes = loader.get_meshes("assets/sponza-minus.obj");

  auto pl2 = std::make_shared<DirLight>(glm::vec3{-1, -1, -1}, glm::vec3{1, 1, 1});
  pl2->ambient_intensity = 0.15f;
  //pl2->set_casts_shadow(true);
  pl2->diffuse_intensity = 0.2f;
  renderer.add_light(pl2);
  
  /*
  auto sphere = std::make_shared<RenderObject>(sphere_mesh);
  sphere->translate({0, 1, 2});
  sphere->scale({0.5, 0.5, 0.5});
  renderer.add_object(sphere);

  int from = -5;
  int to = 5;
  for(int i = from; i < to; i++) {
    for(int j = from; j < to; j++) {
      auto floor = std::make_shared<RenderObject>(floor_mesh);
      floor->translate({i * 4,-1,j * 4});
      floor->scale({2, 1, 2});
      renderer.add_object(floor);
      if(((i % 2 == 0) || (j % 2 == 0)) && 0) {
	auto cube = std::make_shared<RenderObject>(cube_mesh);
	cube->translate({i * 4, 0, j * 4});
	renderer.add_object(cube);
      }
    }
  }
  */

  /*
  auto floor = std::make_shared<RenderObject>(floor_mesh);
  floor->translate({0, -0.5, 0});
  floor->scale({2, 2, 2});
  renderer.add_object(floor);


  auto cube = std::make_shared<RenderObject>(cube_mesh);
  cube->translate({0, -0.5, 0});
  renderer.add_object(cube);

  */
  for(auto& sponza_mesh: sponza_meshes) {
    auto mesh = std::make_shared<RenderObject>(sponza_mesh);
    mesh->transform.scale({0.05, 0.05, 0.05});
    renderer.add_object(mesh);
  }

  std::shared_ptr<SkyBox> sky = std::make_shared<SkyBox>(camera, skydome_mesh);
  sky->transform.scale({2,2,2});
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
    renderer.get_shown_light()->translate({0, -0.01f, 0});
  }, true);
  Input::on(GLFW_KEY_PAGE_UP, [&] {
    if(selected_light < renderer.light_count()) {
      renderer.show_single_light(++selected_light);
    }
  }, false);

  Input::on(GLFW_KEY_DELETE, [&] {
    renderer.clear_lights();
  }, false);
  Input::on(GLFW_KEY_PAGE_DOWN, [&] {
    if(selected_light > 0) {
      renderer.show_single_light(--selected_light);
    }
  }, false);
  Input::on(GLFW_KEY_1, [&] {
      renderer.toggle_shadow_map();
  }, false);
  Input::on(GLFW_KEY_P, [&] {
      if(Input::is_alt_down()) {
        auto light = std::make_shared<PointLight>(camera.pos, get_random_color());
        light->set_casts_shadow(false);
        light->ambient_intensity = 0.0f;
        light->diffuse_intensity = 0.2f;
        renderer.add_light(light);
      } else {
        auto light = std::make_shared<SpotLight>(camera.pos, camera.dir, glm::vec3{1,1,1});
        light->set_casts_shadow(true);
        light->ambient_intensity = 0.0f;
        light->diffuse_intensity = 2.0f;
        renderer.add_light(light);
      }
      std::cout << "Amount of lights: " << renderer.light_count() << "\n";
  }, false);
  Input::on(GLFW_KEY_RIGHT_CONTROL, [&] {
      renderer.show_single_light(-1);
  }, false);
  bool draw_main = true;
  Input::on(GLFW_KEY_T, [&] {
      draw_main = !draw_main;
  }, false);

  nvgCreateFont(vg, "sans", "/usr/share/fonts/truetype/freefont/FreeSans.ttf");
  camera.translate({0, 2, 0});
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    Input::handle_input();
    rotate_camera(camera);
    renderer.pre_render();

    if(draw_main) {
      renderer.render();
    }
    draw_rain(&renderer);

    glfwSwapBuffers(window);

    Input::reset_delta();
    calcFPS(window, 1.0, "Current FPS: ");
    checkForGlError();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

