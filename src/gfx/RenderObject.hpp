#ifndef HONDO_RENDEROBJECT_HPP
#define HONDO_RENDEROBJECT_HPP
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <memory>
#include <string>

#include "Mesh.hpp"
#include "Transform.hpp"
#include "VertexArray.hpp"
#include "Entity.hpp"
#include "AABB.hpp"
#include "shader/SimpleShader.hpp"
class RenderObject {
  friend class SceneGraph;
  friend class Renderer;
  private:
    void swap(RenderObject& first, RenderObject& second);
    Transform transform;
  public:
    RenderObject();
    RenderObject(Mesh& mesh);

    Entity entity;
    Mesh mesh;
    AABB aabb;

    void render();
    void bind_diffuse() const;
    void bind_normal() const;
    void bind_specular() const;
    void bind_mask() const;
    void update_aabb();
};
#endif
