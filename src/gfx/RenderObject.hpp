#ifndef __HONDO_RENDEROBJECT_H__
#define __HONDO_RENDEROBJECT_H__
class RenderObject;

#include "ObjLoader.hpp"
#include "RenderObject.hpp"
#include "VertexArray.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <string>
#include <memory>
class RenderObject {
  private:
    const Mesh mesh;
  public:
    RenderObject(std::shared_ptr<VertexArray> vArray, Mesh mesh);

    const std::shared_ptr<VertexArray> vertex_array;
    glm::vec3 color;
    glm::mat4 model_matrix;

    void render() const;
    void translate(const glm::vec3& pos);
};
#endif
