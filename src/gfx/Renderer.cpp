#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
Renderer::Renderer(int width, int height):
  mvpMat(1.0f),
  perspectiveMat(glm::perspective<float>(45.0f, width/height, 0.1f, 100.0f))
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
    glm::mat4 mvpMat = glm::mat4();
    mvpMat *= this->perspectiveMat;
    mvpMat *= camera->viewMat;
    mvpMat *= rObj->modelMatrix;
    shader.setMVP(mvpMat);
    rObj->render();
  }
}
