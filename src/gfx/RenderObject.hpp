#ifndef __HONDO_RENDEROBJECT_H__
#define __HONDO_RENDEROBJECT_H__
class RenderObject;
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <memory>
#include <string>

#include "Mesh.hpp"
#include "RenderObject.hpp"
#include "VertexArray.hpp"
#include "shader/SimpleShader.hpp"
class RenderObject {
  private:
    void swap(RenderObject& first, RenderObject& second);
  public:
    RenderObject(const VertexArray& vertex_array, const Mesh& mesh);
    RenderObject(const RenderObject& other);

    const Mesh& mesh;
    const VertexArray& vertex_array;
    glm::vec3 pos, scale_val;
    glm::mat4 model_matrix;
    glm::quat rot;

    void render() const;
    void translate(const glm::vec3& pos);
    void scale(const glm::vec3& scale);
    void rotate(float angle, const glm::vec3& axis);
    const glm::mat4& get_model_matrix();
    void set_position(const glm::vec3& pos);
    void bind_diffuse() const;
    void bind_normal() const;
    void bind_specular() const;
};
#endif
