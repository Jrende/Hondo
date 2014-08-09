#include "Renderer.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
Renderer::Renderer(int width, int height):
  perspective_mat(glm::perspective<float>(45.0f, (float) width/ (float) height, 0.1f, 100.0f)) {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);
  }


Renderer::Renderer(const Renderer& other) { }

void Renderer::add_object(const std::shared_ptr<RenderObject>& rObj) {
  render_map[rObj->vertex_array].push_back(rObj);
}

void Renderer::set_camera(std::shared_ptr<Camera> camera) {
  this->camera = camera;
}

void Renderer::render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shader();
  for(const auto& entry: render_map) {
    //Is there a way to load identity without instanciating a new mat4?
    entry.first->bind();
    for(const auto& render_object: entry.second) {
      glm::mat4 mvp_mat = glm::mat4();
      mvp_mat *= this->perspective_mat;
      mvp_mat *= camera->get_view_mat();
      mvp_mat *= render_object->model_matrix;
      shader.set_MVP(mvp_mat);
      shader.set_color(render_object->color);
      render_object->bind_material(shader);
      render_object->render();
    }
    entry.first->unbind();
  }
}

int mode = 0;
void Renderer::toggle_wireframe() {
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

