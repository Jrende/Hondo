#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
Renderer::Renderer(int width, int height):
  perspective_mat(glm::perspective<float>(45.0f, width/height, 0.1f, 100.0f))
{}

void Renderer::addObject(std::shared_ptr<RenderObject> rObj) {
  renderList.push_back(rObj);
}

void Renderer::setCamera(std::shared_ptr<Camera> camera) {
  this->camera = camera;
}

void Renderer::render() {
  shader();
  for(auto rObj: renderList) {
    //Is there a way to load identity without instanciating a new mat4?
    glm::mat4 mvp_mat = glm::mat4();
    mvp_mat *= this->perspective_mat;
    mvp_mat *= camera->view_mat;
    mvp_mat *= rObj->modelMatrix;
    shader.setMVP(mvp_mat);
    rObj->render();
  }
}
