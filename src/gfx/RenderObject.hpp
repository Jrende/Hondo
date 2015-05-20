#ifndef HONDO_RENDEROBJECT_HPP
#define HONDO_RENDEROBJECT_HPP
class RenderObject;
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <memory>
#include <string>

#include "Mesh.hpp"
#include "RenderObject.hpp"
#include "Transform.hpp"
#include "VertexArray.hpp"
#include "shader/SimpleShader.hpp"
class RenderObject {
  private:
    void swap(RenderObject& first, RenderObject& second);
  public:
    Transform transform;
    RenderObject(Mesh& mesh);

    Mesh& mesh;

    void render();
    void bind_diffuse() const;
    void bind_normal() const;
    void bind_specular() const;
    void bind_mask() const;
};
#endif
