#pragma once
#include <array>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iterator>
class AABB {
  private:
    //Maybe const, and just mult with model mat every frame...
    //Or update every transform
    std::array<glm::vec3, 8> base_cube;
  public:
    std::array<glm::vec3, 8> cube;
    AABB();
    AABB(std::array<glm::vec3, 6> points);
    AABB(std::array<std::array<float, 3>, 6> point_array);
    void transform(const glm::mat4& model_mat);

    template<typename Iterator>
    std::array<glm::vec3, 8> create_aabb_from_points(Iterator begin, Iterator end) {
      std::array<glm::vec3, 8> new_cube;
      const auto& f = *begin;
      new_cube.fill({f[0], f[1], f[2]});
      for(auto it = begin; it != end; ++it) {
        const auto& p = *it;
        if(new_cube[0].x < p[0])
          new_cube[0].x = p[0];
        if(new_cube[0].y < p[1])
          new_cube[0].y = p[1];
        if(new_cube[0].z < p[2])
          new_cube[0].z = p[2];

        if(new_cube[1].x > p[0])
          new_cube[1].x = p[0];
        if(new_cube[1].y < p[1])
          new_cube[1].y = p[1];
        if(new_cube[1].z < p[2])
          new_cube[1].z = p[2];

        if(new_cube[2].x < p[0])
          new_cube[2].x = p[0];
        if(new_cube[2].y > p[1])
          new_cube[2].y = p[1];
        if(new_cube[2].z < p[2])
          new_cube[2].z = p[2];

        if(new_cube[3].x > p[0])
          new_cube[3].x = p[0];
        if(new_cube[3].y > p[1])
          new_cube[3].y = p[1];
        if(new_cube[3].z < p[2])
          new_cube[3].z = p[2];

        if(new_cube[4].x < p[0])
          new_cube[4].x = p[0];
        if(new_cube[4].y < p[1])
          new_cube[4].y = p[1];
        if(new_cube[4].z > p[2])
          new_cube[4].z = p[2];

        if(new_cube[5].x > p[0])
          new_cube[5].x = p[0];
        if(new_cube[5].y < p[1])
          new_cube[5].y = p[1];
        if(new_cube[5].z > p[2])
          new_cube[5].z = p[2];

        if(new_cube[6].x < p[0])
          new_cube[6].x = p[0];
        if(new_cube[6].y > p[1])
          new_cube[6].y = p[1];
        if(new_cube[6].z > p[2])
          new_cube[6].z = p[2];

        if(new_cube[7].x > p[0])
          new_cube[7].x = p[0];
        if(new_cube[7].y > p[1])
          new_cube[7].y = p[1];
        if(new_cube[7].z > p[2])
          new_cube[7].z = p[2];
      }
      return new_cube;
    }
};
