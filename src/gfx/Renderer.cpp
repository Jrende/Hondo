#include "Renderer.hpp"
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <math.h>
#include <memory>
#include <stdlib.h>
#include "../ui/DebugText.hpp"
Renderer::Renderer(int width, int height):
  width(width),
  height(height),
  perspective_mat(glm::perspective<float>(45.0f, (float) width/height, 0.5f, 50.0f)),
  point_light_shader(std::make_shared<PointLightShader>()),
  spot_light_shader(std::make_shared<SpotLightShader>()),
  dir_light_shader(std::make_shared<LightShader>()),
  ortho(glm::ortho<float>(-10,10,-10,10,-0,10)),
  depth_bias_mat(
      0.5, 0.0, 0.0, 0.0,
      0.0, 0.5, 0.0, 0.0,
      0.0, 0.0, 0.5, 0.0,
      0.5, 0.5, 0.5, 1.0
      )
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  lights[point_light_shader];
  lights[spot_light_shader];
  lights[dir_light_shader];
}

void Renderer::set_camera(std::shared_ptr<Camera> camera) {
  this->camera = camera;
}

bool draw_shadow_map = false;
void Renderer::pre_render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glDepthMask(GL_TRUE);

  glFrontFace(GL_CCW);

  if(shown_light_index != -1 && draw_shadow_map) {
    debug_renderer.render_fbo(light_list[shown_light_index]->shadow_map.depth_tex);
  }
}

void Renderer::render_depth_test(std::vector<RenderObject>& render_list) {
  depth_shader.use_shader();
  for(auto& light: light_list) {
    if(light->casts_shadow()) {
      glViewport(0.0f, 0.0f, (float) light->shadow_map.width, (float) light->shadow_map.height);
      glm::mat4 vp_mat;
      vp_mat *= light->get_projection();
      vp_mat *= light->get_view_mat();

      light->shadow_map.bind();
      glClear(GL_DEPTH_BUFFER_BIT);
      render_scene(vp_mat, render_list);
      light->shadow_map.unbind();
    }
  }
  depth_shader.stop();
  glViewport(0.0f, 0.0f, width, height);
}

void Renderer::render_scene(const glm::mat4& vp_mat, std::vector<RenderObject>& render_list) {
  VertexArray& vertex_format = (*render_list[0].mesh.vertex_array);
  vertex_format.bind();
  for(auto& render_object: render_list) {
    if((*render_object.mesh.vertex_array) != vertex_format) {
      vertex_format.unbind();
      vertex_format = (*render_object.mesh.vertex_array);
      vertex_format.bind();
    }
    const glm::mat4& obj_model_mat = render_object.transform.get_model_matrix();
    depth_shader.set_mvp_mat(vp_mat * obj_model_mat);

    depth_shader.set_mask_sampler(3);
    render_object.bind_mask();

    render_object.render();
  }
}

void Renderer::render(std::vector<RenderObject>& render_list) {
  int draw_calls = 0;
  pre_render();
  render_depth_test(render_list);

  glDisable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE);
  //foreach type of light
  for(auto& light_type: lights) {
    if(light_type.second.size() == 0) {
      continue;
    }
    std::shared_ptr<LightShader> shader = light_type.first;
    //foreach light instance
    for(auto& light: light_type.second) {
      draw_point(light->get_pos());
    }
    shader->use_shader();
    for(auto& light: light_type.second) {
      if(shown_light_index != -1 && light_list[shown_light_index] != light) {
        continue;
      }
      //Might need static_cast
      shader->set_light(*light);
      //foreach vertex format
      VertexArray& vertex_format = (*render_list[0].mesh.vertex_array);
      vertex_format.bind();
      for(auto& render_object: render_list) {
        if((*render_object.mesh.vertex_array) != vertex_format) {
          vertex_format.unbind();
          vertex_format = (*render_object.mesh.vertex_array);
          vertex_format.bind();
        }
        const glm::mat4& obj_model_mat = render_object.transform.get_model_matrix();

        glm::mat4 mvp_mat = glm::mat4();
        mvp_mat *= perspective_mat;
        mvp_mat *= camera->get_view_mat();
        mvp_mat *= obj_model_mat;
        shader->set_mvp_mat(mvp_mat);
        shader->set_model_mat(obj_model_mat);

        shader->set_eye_pos(camera->pos);
        shader->set_eye_dir(camera->dir);

        shader->set_diffuse_sampler(0);
        render_object.bind_diffuse();

        shader->set_normal_sampler(1);
        render_object.bind_normal();

        shader->set_specular_sampler(2);
        render_object.bind_specular();

        shader->set_mask_sampler(3);
        render_object.bind_mask();

        if(light->casts_shadow()) {
          glm::mat4 depth_mvp_mat = glm::mat4();
          depth_mvp_mat *= light->get_projection();
          depth_mvp_mat *= light->get_view_mat();
          depth_mvp_mat *= obj_model_mat;
          depth_mvp_mat = depth_bias_mat * depth_mvp_mat;
          shader->set_depth_mvp_mat(depth_mvp_mat);

          light->shadow_map.bind_shadowmap(GL_TEXTURE4);
          shader->set_shadow_sampler(4);
        }

        shader->set_material(render_object.mesh.material);
        draw_calls++;
        render_object.render();
      }
      glEnable(GL_BLEND);
    }
  }
  draw_sky();
  DebugText::set_value("draw calls", draw_calls);
}

void Renderer::draw_lines(const std::vector<std::pair<glm::vec3, glm::vec3>>& lines, const glm::vec3& color) {
  glEnable(GL_BLEND);
  glm::mat4 mvp_mat = glm::mat4();
  mvp_mat *= perspective_mat;
  mvp_mat *= camera->get_view_mat();
  debug_renderer.draw_lines(lines, mvp_mat, color);
}

void Renderer::draw_line(const glm::vec3& from, const glm::vec3& to, const glm::vec3& color) {
  glEnable(GL_BLEND);
  glm::mat4 mvp_mat = glm::mat4();
  mvp_mat *= perspective_mat;
  mvp_mat *= camera->get_view_mat();
  debug_renderer.draw_line(from, to, mvp_mat, color);
}

void Renderer::draw_point(const glm::vec3& pos) {
  glm::mat4 mvp_mat = glm::mat4();
  mvp_mat *= perspective_mat;
  mvp_mat *= camera->get_view_mat();
  debug_renderer.draw_point(pos, mvp_mat);
}

void Renderer::toggle_wireframe() {
  static int mode = 0;
  mode++;
  switch(mode) {
    default:
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      mode = 0;
      break;
    case 1:
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      break;
    case 2:
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
      break;
  }
}

void Renderer::add_light(std::shared_ptr<PointLight> point_light) {
  lights[point_light_shader].push_back(point_light);
  light_list.push_back(point_light);
  DebugText::set_value("Num lights", light_count());
}

void Renderer::add_light(std::shared_ptr<SpotLight> spot_light) {
  lights[spot_light_shader].push_back(spot_light);
  light_list.push_back(spot_light);
  DebugText::set_value("Num lights", light_count());
}

void Renderer::add_light(std::shared_ptr<DirLight> dir_light) {
  lights[dir_light_shader].push_back(dir_light);
  light_list.push_back(dir_light);
  DebugText::set_value("Num lights", light_count());
}

void Renderer::show_single_light(int index) {
  last_shown_light_index = fmax(0, shown_light_index);
  index = fmax(-1, fmin(index, light_list.size() - 1));
  std::cout << "Show light " << index << "\n";
  shown_light_index = index;
}

std::shared_ptr<Light> Renderer::get_shown_light() {
  if(shown_light_index == -1) {
    return light_list[last_shown_light_index];
  } else {
    return light_list[shown_light_index];
  }
}

int Renderer::light_count() {
  return light_list.size();
}

void Renderer::set_skybox(RenderObject&& skybox) {
  this->skybox = std::make_unique<RenderObject>(skybox);
}

void Renderer::draw_sky() {
  if(skybox) {
    glDepthFunc(GL_EQUAL);
    glDepthRange(1, 1);
    skybox->transform.set_position(camera->pos);
    sky_shader();
    glm::mat4 mvp_mat = glm::mat4();
    mvp_mat *= perspective_mat;
    mvp_mat *= camera->get_view_mat();
    sky_shader.set_mvp_mat(mvp_mat);
    sky_shader.set_model_mat(skybox->transform.get_model_matrix());
    skybox->mesh.vertex_array->bind();
    skybox->render();
    skybox->mesh.vertex_array->unbind();
    sky_shader.stop();
    glDepthRange(0, 1);
    glDepthFunc(GL_LEQUAL);
  }
}

void Renderer::toggle_shadow_map() {
  draw_shadow_map = !draw_shadow_map;
}

void Renderer::clear_lights() {
  lights.clear();
  light_list.clear();
  DebugText::set_value("Num lights", 0);
}

bool vertex_array_sort(const RenderObject& left, const RenderObject& right) {
  return (*left.mesh.vertex_array) == (*right.mesh.vertex_array);
}

void Renderer::render(World& world) {
  render(world.render_list);
}
