#ifndef HONDO_LIGHT_HPP
#define HONDO_LIGHT_HPP
class Light;
#define GLM_FORCE_RADIANS
#include <boost/optional.hpp>
#include <glm/glm.hpp>
#include "../Camera.hpp"
#include "../DepthBuffer.hpp"
class Light {
  private:
    Camera camera;
    bool m_has_moved = true;
  public:
    glm::vec3 color;
    float ambient_intensity, diffuse_intensity;

    const glm::vec3& get_pos() const;
    const glm::vec3& get_dir() const;

    const glm::mat4& get_view_mat() const;
    bool has_moved();
    void translate(glm::vec3 pos);

    Light(glm::vec3 pos, glm::vec3 dir, glm::vec3 color);
};
#endif
