#ifndef HONDO_CAMERA_HPP
#define HONDO_CAMERA_HPP
class Camera;
#include "RenderObject.hpp"
#include <glm/gtc/quaternion.hpp>
class Camera {
  private:
  public:
    glm::vec3 up,pos,dir;
    glm::quat rot;
    glm::mat4 view_mat;
    void translate(glm::vec3 pos);
    const glm::mat4& get_view_mat();
    void rotate(float angle, glm::vec3 axis);
    void move_forward(float dist);
    void move_right(float dist);
    Camera();
};
#endif
