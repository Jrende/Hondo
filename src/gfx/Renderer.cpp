#include "Renderer.hpp"
#include <memory>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <stdlib.h>
Renderer::Renderer(int width, int height):
  perspective_mat(glm::perspective<float>(45.0f, (float) width/ (float) height, 0.1f, 100.0f)),
  debug_renderer(),
  camera(),
  point_light_shader(std::make_shared<PointLightShader>())
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glDepthMask(GL_TRUE);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);
  lights[point_light_shader];
}

void Renderer::add_object(std::shared_ptr<RenderObject> rObj) {
  render_map[rObj->vertex_array].push_back(rObj);
}

Camera& Renderer::get_camera() {
  return camera;
}

void Renderer::render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE);
  //foreach type of light
  for(auto& light_type: lights) {
    auto& shader = light_type.first;

    shader->use_shader();
    //Remove when lights are implemented
    //foreach light instance
    for(auto& light: light_type.second) {
      //Might need static_cast
      shader->set_light(*light);
      //foreach vertex format
      for(auto& vertex_format: render_map) {
	vertex_format.first.bind();
	for(auto& render_object: vertex_format.second) {
	  glm::mat4 mvp_mat = glm::mat4();
	  mvp_mat *= this->perspective_mat;
	  mvp_mat *= camera.get_view_mat();
	  mvp_mat *= render_object->get_model_matrix();
	  shader->set_mvp_mat(mvp_mat);
	  shader->set_model_mat(render_object->get_model_matrix());
	  
	  shader->set_eye_pos(camera.pos);
	  shader->set_eye_dir(camera.dir);

	  shader->set_diffuse_sampler(0);
	  render_object->bind_diffuse();

	  shader->set_normal_sampler(1);
	  render_object->bind_normal();

	  shader->set_specular_sampler(2);
	  render_object->bind_specular();

	  shader->set_material(render_object->mesh.material);

	  render_object->render();
	}
	vertex_format.first.unbind();
      }
      glEnable(GL_BLEND);
    }
  }
}

void Renderer::draw_line(const glm::vec3& from, const glm::vec3& to, const glm::vec3& color) {
  glm::mat4 mvp_mat = glm::mat4();
  mvp_mat *= this->perspective_mat;
  mvp_mat *= camera.get_view_mat();
  debug_renderer.draw_line(from, to, mvp_mat, color);
}

void Renderer::draw_point(const glm::vec3& pos) {
  glm::mat4 mvp_mat = glm::mat4();
  mvp_mat *= this->perspective_mat;
  mvp_mat *= camera.get_view_mat();
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

void Renderer::add_light(std::shared_ptr<Light> point_light) {
  lights[point_light_shader].push_back(point_light);
}
