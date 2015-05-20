#pragma once
class Transform;
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
class Transform {
  private:
  protected:
    glm::vec3 pos, scale_val;
    glm::quat rot;
    glm::mat4 model_matrix;
  public:
    Transform();
    void translate(const glm::vec3& pos);
    void set_position(const glm::vec3& pos);
    void scale(const glm::vec3& scale);
    void rotate(float angle, const glm::vec3& axis);
    const glm::mat4& get_model_matrix();
};
