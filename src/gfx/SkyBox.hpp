#ifndef HONDO_SKYBOX_HPP
#define HONDO_SKYBOX_HPP
class SkyBox;
#include "Camera.hpp"

class SkyBox: public RenderObject {
  private:
    const Camera& camera;
  public:
    SkyBox(Camera const& camera, const VertexArray& vertex_array, const Mesh& mesh);
    void update_pos();
};
#endif
