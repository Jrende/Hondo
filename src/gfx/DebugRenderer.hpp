#ifndef HONDO_DEBUGRENDERER_HPP
#define HONDO_DEBUGRENDERER_HPP
class DebugRenderer;
#include <vector>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "shader/debugshader/DebugShader.hpp"
#include "shader/debugshader/LineShader.hpp"
#include "Camera.hpp"
#include "VertexArray.hpp"
class DebugRenderer {
  private:
    DebugRenderer(const DebugRenderer& other);
    DebugShader debug_shader;
    LineShader line_shader;
    VertexArray vertex_array;
  public:
    DebugRenderer();
    void draw_point(const glm::vec3& pos, const glm::mat4& vp_mat);
    void draw_line(const glm::vec3& from, const glm::vec3& to, const glm::mat4& vp_mat);
};
#endif
