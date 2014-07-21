#ifndef __HONDO_RENDEROBJECT_H__
#define __HONDO_RENDEROBJECT_H__
class RenderObject;
#include <string>
#include "RenderObject.h"
#include "VertexArray.h"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <memory>
class RenderObject {
  private:
    const std::shared_ptr<VertexArray> vArray;
  public:
    glm::vec3 color;
    glm::mat4 model_matrix;
    RenderObject(std::shared_ptr<VertexArray> vArray);
    RenderObject(const RenderObject& other);
    void render();
    void translate(const glm::vec3& pos);
};
#endif
