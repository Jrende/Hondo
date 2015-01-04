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
    bool m_casts_shadow = false;
    bool m_has_moved = true;
  public:
    DepthBuffer shadow_map;
    glm::vec3 color;
    float ambient_intensity, diffuse_intensity;
    glm::mat4 perspective_mat;

    const glm::vec3& get_pos() const;
    const glm::vec3& get_dir() const;

    const glm::mat4& get_view_mat() const;
    virtual const glm::mat4& get_projection() const;
    bool casts_shadow();
    bool has_moved();
    void set_has_moved(bool has_moved);
    void translate(glm::vec3 pos);
    void set_casts_shadow(bool casts_shadow);

    Light(glm::vec3 pos, glm::vec3 dir, glm::vec3 color);
};
#endif
