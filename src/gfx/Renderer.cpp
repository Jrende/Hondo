#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include "Renderer.h"
void Renderer::addObject(std::shared_ptr<RenderObject> rObj) {
  renderList.push_back(rObj);
}

Renderer::Renderer() {}

void Renderer::render() {
  for(auto rObj: renderList) {
    shader.setModelMatrix(rObj->modelMatrix);
    rObj->render();
  }
}
