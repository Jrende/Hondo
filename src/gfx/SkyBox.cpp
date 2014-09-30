
#include "SkyBox.hpp"
SkyBox::SkyBox(Camera const& camera, const VertexArray& vertex_array, const Mesh& mesh):
  RenderObject(vertex_array, mesh),
  camera(camera)
{

}


void SkyBox::update_pos() {
  this->set_position(camera.pos);
}
