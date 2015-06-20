#pragma once
class Transform;
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
class Transform {
  friend class RenderObject;
  private:
  protected:
    glm::vec3 pos, scale_val;
    glm::quat rot;
  public:
    Transform();
    glm::mat4 model_matrix;
    void set_position(const glm::vec3& pos);
    void translate(const glm::vec3& pos);
    void scale(const glm::vec3& scale);
    void rotate(float angle, const glm::vec3& axis);
    void rotate(const glm::quat& rot);

    const glm::vec3& get_pos();
    const glm::quat& get_rot();
    const glm::vec3& get_scale();

    const glm::mat4& get_model_matrix();
};
