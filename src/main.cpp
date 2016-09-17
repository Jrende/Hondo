#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <nanovg.h>
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg_gl.h>

#include "gfx/Renderer.hpp"
#include "gfx/World.hpp"
#include "gfx/Entity.hpp"
#include "gfx/VertexArray.hpp"
#include "gfx/SkyBox.hpp"
#include "gfx/importer/ObjLoader.hpp"
#include "gfx/lights/Light.hpp"
#include "gfx/lights/PointLight.hpp"
#include "gfx/lights/DirLight.hpp"
#include "gfx/shader/SimpleShader.hpp"

#include "input/Actions.hpp"
#include "input/Input.hpp"

#include "ui/DebugText.hpp"

#include "game/FPSController.hpp"
#include "DebugUtils.h"

void glDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *msg, void *data) {
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

int selected_light = -1;

int width = 1024;
int height = 768;
int main(int argc, char ** argv) {
  glfwSetErrorCallback(error_callback);
  if (!glfwInit())
    exit(EXIT_FAILURE);

  bool fullscreen = false;
  for(int i = 0; i < argc; i++) {
    //std::cout << argv[i] << "\n";
    if(!strcmp(argv[i], "-w")) {
      width = atoi(argv[i+1]);
    }
    if(!strcmp(argv[i], "-h")) {
      height = atoi(argv[i+1]);
    }
    if(!strcmp(argv[i], "-f")) {
      fullscreen = true;
    }

  }
  std::cout << "w: " << width << "\nheight: " << height << "\n";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint( GLFW_OPENGL_DEBUG_CONTEXT, true );

  GLFWwindow* window = nullptr; 
  if(fullscreen) {
    const auto& monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    glfwWindowHint(GLFW_SAMPLES, 8);
    window = glfwCreateWindow(mode->width, mode->height, "Hondo", monitor, NULL);
    width = mode->width;
    height = mode->height;
  } else {
    window = glfwCreateWindow(width, height, "Hondo", NULL, NULL);
  }

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
    glfwSetScrollCallback(window, Input::scroll_callback);
    Input::set_active_window(window);
  }
  Renderer renderer(width, height);

  struct NVGcontext* vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_DEBUG);
  //glDebugMessageCallback(glDebugCallback, NULL );
  FPSController fpsController;
  renderer.set_camera(fpsController.get_camera());

  const auto& camera = fpsController.get_camera();

  Input::on(GLFW_KEY_Z, [&] {
      renderer.toggle_wireframe();
  });

  Input::on(GLFW_KEY_X, [&] {
      renderer.toggle_debug();
  });

  Input::on(GLFW_KEY_G, []() {
    Input::lock_mouse();
  });
  ObjLoader loader;
  loader.preload_file("assets/sponza-minus.obj");
  loader.preload_file("assets/Cube.obj");
  loader.preload_file("assets/sphere.obj");
  loader.preload_file("assets/SkyDome16.obj");
  loader.load_files();
  Mesh skydome_mesh = loader.get_meshes("assets/SkyDome16.obj")[0];
  Mesh cube_mesh = loader.get_meshes("assets/Cube.obj")[0];
  Mesh sphere_mesh = loader.get_meshes("assets/sphere.obj")[0];
  std::vector<Mesh> sponza_meshes = loader.get_meshes("assets/sponza-minus.obj");

  auto pl2 = std::make_shared<DirLight>(glm::vec3{-0, -1, -1}, glm::vec3{1, 1, 1});
  pl2->ambient_intensity = 0.25f;
  pl2->diffuse_intensity = 0.5f;
  renderer.add_light(pl2);

  World world;

  //Entity cube = world.create_entity(RenderObject(cube_mesh));
  //world.scale(cube, glm::vec3{0.5, 0.5, 0.5});
  //world.translate(cube, glm::vec3{0, 2, 0});
  Entity sponza = world.create_empty_entity();
  for(auto& sponza_mesh: sponza_meshes) {
    if(sponza_mesh.name == "bricks") {
      static int count = 0;
      std::cout << "Create " << sponza_mesh.name << " num " << count++ << '\n';
    }
    world.create_entity(sponza, RenderObject(sponza_mesh));
  }
  world.scale(sponza, {0.1, 0.1, 0.1});
  /*

  Entity cube = world.create_entity(RenderObject(cube_mesh));
  world.scale(cube, glm::vec3{0.5, 0.5, 0.5});
  world.translate(cube, glm::vec3{0, 2, 0});
  Entity sphere1 = world.create_entity(cube, RenderObject(sphere_mesh));
  world.translate(sphere1, glm::vec3{2, 0, 0});

  Entity sphere2 = world.create_entity(cube, RenderObject(sphere_mesh));
  world.translate(sphere2, glm::vec3{-2, 0, 0});
  Entity sphere3 = world.create_entity(cube, RenderObject(sphere_mesh));
  world.translate(sphere3, glm::vec3{0, 0, 2});
  Entity sphere6 = world.create_entity(sphere3, RenderObject(sphere_mesh));
  world.translate(sphere6, glm::vec3{0, 2, 0});
  world.scale(sphere6, glm::vec3{0.5, 0.5, 0.5});

  Entity sphere4 = world.create_entity(cube, RenderObject(sphere_mesh));
  world.translate(sphere4, glm::vec3{0, 0, -2});
  Entity sphere5 = world.create_entity(sphere4, RenderObject(sphere_mesh));
  world.translate(sphere5, glm::vec3{0, 2, 0});
  world.scale(sphere5, glm::vec3{0.5, 0.5, 0.5});
  */

  renderer.set_skybox(RenderObject(skydome_mesh));

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

      /*
  Input::on(GLFW_KEY_COMMA, [&] {
      world.translate(cube, glm::vec3{0, 0, -0.1});
  }, true);
  Input::on(GLFW_KEY_PERIOD, [&] {
      world.translate(cube, glm::vec3{0, 0, 0.1});
  }, true);

  Input::on(GLFW_KEY_N, [&] {
      world.translate(cube, glm::vec3{0, -0.1, 0});
  }, true);
  Input::on(GLFW_KEY_M, [&] {
      world.translate(cube, glm::vec3{0, 0.1, 0});
  }, true);

  Input::on(GLFW_KEY_V, [&] {
      world.translate(cube, glm::vec3{-0.1, 0, 0});
  }, true);
  Input::on(GLFW_KEY_B, [&] {
      world.translate(cube, glm::vec3{0.1, 0, 0});
  }, true);

  Input::on(GLFW_KEY_V, [&] {
      world.translate(cube, glm::vec3{-0.1, 0, 0});
  }, true);
  Input::on(GLFW_KEY_B, [&] {
      world.translate(cube, glm::vec3{0.1, 0, 0});
  }, true);
  */

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
        auto light = std::make_shared<PointLight>(camera->pos, get_random_color());
        light->set_casts_shadow(false);
        light->ambient_intensity = 0.0f;
        light->diffuse_intensity = 0.2f;
        renderer.add_light(light);
      } else {
        auto light = std::make_shared<SpotLight>(camera->pos, camera->dir, glm::vec3{1,1,1});
        light->set_casts_shadow(true);
        light->ambient_intensity = 0.0f;
        light->diffuse_intensity = 2.0f;
        renderer.add_light(light);
      }
  }, false);
  Input::on(GLFW_KEY_RIGHT_CONTROL, [&] {
      renderer.show_single_light(-1);
  }, false);
  bool draw_main = true;
  Input::on(GLFW_KEY_T, [&] {
      draw_main = !draw_main;
  }, false);

  nvgCreateFont(vg, "sans", "/usr/share/fonts/truetype/freefont/FreeSans.ttf");

  DebugText::set_context(vg);

  camera->translate({0, 2, 0});
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    Input::handle_input();
    fpsController.handle_mouse();
    fpsController.handle_movement();
    renderer.render(world);
    if(draw_main) {
      /*
      world.rotate(cube, 0.01, glm::vec3{1, 1, 0});
      world.rotate(sphere1, -0.01, glm::vec3{0, 1, 0});
      world.rotate(sphere2, -0.01, glm::vec3{0, 1, 0});
      world.rotate(sphere3, -0.01, glm::vec3{0, 0, 1});
      world.rotate(sphere4,  0.01, glm::vec3{0, 0, 1});
      */
    }

    std::stringstream str;
    str << std::fixed << std::setprecision(1) << calcFPS(1.0);
    DebugText::set_value("fps", str.str().c_str());

    nvgBeginFrame(vg, width, height, 1);
    DebugText::draw();
    nvgEndFrame(vg);

    glfwSwapBuffers(window);

    Input::reset_delta();
    checkForGlError();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

