#ifndef HONDO_CAMERA_HPP
#define HONDO_CAMERA_HPP
class Camera;
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>
class Camera {
  private:
    void calc_view_mat();
  public:
    glm::vec3 up,pos,dir;
    glm::quat rot;
    glm::mat4 view_mat;
    void translate(glm::vec3 pos);
    const glm::mat4& get_view_mat() const;
    void rotate(float angle, glm::vec3 axis);
    void move_forward(float dist);
    void move_right(float dist);
    Camera(
	glm::vec3 pos = glm::vec3(0, 0, 0),
	glm::vec3 dir = glm::vec3(0, 0, 1.0f));
};
#endif
