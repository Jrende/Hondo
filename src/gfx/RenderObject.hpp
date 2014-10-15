#ifndef HONDO_RENDEROBJECT_HPP
#define HONDO_RENDEROBJECT_HPP
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
    RenderObject(Mesh& mesh);
    RenderObject(const RenderObject& other);

    Mesh& mesh;
    glm::vec3 pos, scale_val;
    glm::quat rot;
    glm::mat4 model_matrix;

    void render();
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
