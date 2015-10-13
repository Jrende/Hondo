#include "AABB.hpp"
#include <glm/gtc/matrix_transform.hpp>

AABB::AABB() {}
AABB::AABB(std::array<glm::vec3, 6> points) {
  base_cube = create_aabb_from_points(points.begin(), points.end());
  cube = base_cube;
}

AABB::AABB(std::array<std::array<float, 3>, 6> points) {
  base_cube = create_aabb_from_points(points.begin(), points.end());
  cube = base_cube;
}

void AABB::transform(const glm::mat4& model_mat) {
  std::array<glm::vec3, 8> mid_cube = base_cube;
  for(glm::vec3& point: mid_cube) {
    glm::vec4 p = model_mat * glm::vec4(point, 1.0);
    point.x = p.x;
    point.y = p.y;
    point.z = p.z;
  }
  cube = create_aabb_from_points(mid_cube.begin(), mid_cube.end());
}
