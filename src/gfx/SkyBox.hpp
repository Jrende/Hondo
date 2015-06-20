#ifndef HONDO_SKYBOX_HPP
#define HONDO_SKYBOX_HPP
class SkyBox;
#include "Camera.hpp"
#include "RenderObject.hpp"

class SkyBox: public RenderObject {
  private:
    const Camera& camera;
  public:
    SkyBox(Camera const& camera, Mesh& mesh);
    void update_pos();
};
#endif
