#ifndef __HONDO_RENDEROBJECT_H__
#define __HONDO_RENDEROBJECT_H__
class RenderObject;
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <string>
#include <memory>

#include "ObjLoader.hpp"
#include "RenderObject.hpp"
#include "VertexArray.hpp"
#include "shader/SimpleShader.hpp"
class RenderObject {
  private:
  public:
    RenderObject(std::shared_ptr<VertexArray> vArray, Mesh mesh);
    RenderObject(const RenderObject& other);

    const std::shared_ptr<VertexArray> vertex_array;
    glm::vec3 color;
    glm::mat4 model_matrix;
    const Mesh mesh;

    void render() const;
    void translate(const glm::vec3& pos);
    void set_position(const glm::vec3& pos);
    void bind_material(SimpleShader& simple_shader) const;
};
#endif
