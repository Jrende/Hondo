#ifndef HONDO_DEBUGRENDERER_HPP
#define HONDO_DEBUGRENDERER_HPP
class DebugRenderer;
#include <vector>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "shader/debugshader/DebugShader.hpp"
#include "shader/debugshader/LineShader.hpp"
#include "shader/FramebufferShader.hpp"
#include "Camera.hpp"
#include "VertexArray.hpp"
class DebugRenderer {
  private:
    DebugRenderer(const DebugRenderer& other);
    DebugShader debug_shader;
    LineShader line_shader;
    VertexArray line;
    VertexArray quad;
    FramebufferShader fbo_shader;
  public:
    DebugRenderer();
    void draw_point(const glm::vec3& pos, const glm::mat4& vp_mat);
    void draw_lines(const std::vector<std::pair<glm::vec3, glm::vec3>>& lines, const glm::mat4& vp_mat, const glm::vec3& color);
    void draw_line(const glm::vec3& from, const glm::vec3& to, const glm::mat4& vp_mat, const glm::vec3& color);
    void render_fbo(const GLuint fbo);
    void draw_aabb(const AABB& aabb, const glm::mat4& vp_mat);
};
#endif
