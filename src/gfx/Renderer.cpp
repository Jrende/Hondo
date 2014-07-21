#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
Renderer::Renderer(int width, int height):
  perspective_mat(glm::perspective<float>(45.0f, width/height, 0.1f, 100.0f)) {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);
  }


Renderer::Renderer(const Renderer& other) { }

void Renderer::add_object(const RenderObject& rObj) {
  renderList.push_back(rObj);
}

void Renderer::set_camera(std::shared_ptr<Camera> camera) {
  this->camera = camera;
}

void Renderer::render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shader();
  for(auto& rObj: renderList) {
    //Is there a way to load identity without instanciating a new mat4?
    glm::mat4 mvp_mat = glm::mat4();
    mvp_mat *= this->perspective_mat;
    mvp_mat *= camera->get_view_mat();
    mvp_mat *= rObj.model_matrix;
    shader.set_MVP(mvp_mat);
    shader.set_color(rObj.color);
    rObj.render();
  }
}
