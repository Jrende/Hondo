
#include "SkyBox.hpp"
SkyBox::SkyBox(Camera const& camera, Mesh& mesh):
  RenderObject(mesh),
  camera(camera)
{

}


void SkyBox::update_pos() {
  this->transform.set_position(camera.pos);
}
