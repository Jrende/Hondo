#include <iostream>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include "DebugRenderer.hpp"

DebugRenderer::DebugRenderer():
  debug_shader(),
  line_shader(),
  line({0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}, {0}, {3}),
  quad(
      {
      -0.5, -0.5, 0.0,
       0.0,  0.0,
      -0.5,  0.5, 0.0,
       0.0,  1.0,
       0.5, -0.5, 0.0,
       1.0,  0.0,
       0.5,  0.5, 0.0,
       1.0,  1.0,
      },
      {0, 3, 1, 0, 2, 3}, {3, 2})
{
  
}

void DebugRenderer::draw_lines(const std::vector<std::pair<glm::vec3, glm::vec3>>& lines, const glm::mat4& vp_mat, const glm::vec3& color) {
  line_shader();
  line_shader.set_color(color);
  line_shader.set_MVP(vp_mat);
  line.bind();
  for(const auto& line: lines) {
    line_shader.set_from(std::get<0>(line));
    line_shader.set_to(std::get<1>(line));
    glDrawArrays(GL_POINTS, 0, 1);
    line_shader.set_from(std::get<1>(line));
    line_shader.set_to(std::get<0>(line));
    glDrawArrays(GL_POINTS, 0, 1);
  }
  line.unbind();
  line_shader.stop();
}

void DebugRenderer::draw_line(const glm::vec3& from, const glm::vec3& to, const glm::mat4& vp_mat, const glm::vec3& color) {
  //Optimization opportunity: No need to rebind shader every line
  //Also, vertex_buffer binding might be reusable between line and point
  line_shader();
  line_shader.set_color(color);
  line_shader.set_MVP(vp_mat);
  line_shader.set_from(from);
  line_shader.set_to(to);
  line.bind();
  glDrawArrays(GL_POINTS, 0, 1);
  line_shader.set_from(to);
  line_shader.set_to(from);
  glDrawArrays(GL_POINTS, 0, 1);
  line.unbind();
  line_shader.stop();
}

void DebugRenderer::draw_point(const glm::vec3& pos, const glm::mat4& vp_mat) {
  debug_shader();
  debug_shader.set_color({1,1,1});
  debug_shader.set_MVP(vp_mat);
  debug_shader.set_pos(pos);
  line.bind();
  glDrawArrays(GL_POINTS, 0, 1);
  line.unbind();
  debug_shader.stop();
}

void DebugRenderer::render_fbo(const GLuint fbo_tex) {
  fbo_shader.use_shader();
  quad.bind();
  fbo_shader.set_framebuffer_sampler(0);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, fbo_tex);
  quad.render_elements(GL_TRIANGLES, 6);
  quad.unbind();
  fbo_shader.stop();
}

// Eeeugh
void DebugRenderer::draw_aabb(const AABB& aabb, const glm::mat4& vp_mat) {
  glm::vec3 white = glm::vec3({1, 1, 1});
  std::vector<std::pair<glm::vec3, glm::vec3>> cube = {
    std::make_pair(aabb.cube[0], aabb.cube[1]),
    std::make_pair(aabb.cube[0], aabb.cube[2]),
    std::make_pair(aabb.cube[0], aabb.cube[4]),
    std::make_pair(aabb.cube[1], aabb.cube[3]),
    std::make_pair(aabb.cube[1], aabb.cube[5]),
    std::make_pair(aabb.cube[2], aabb.cube[3]),
    std::make_pair(aabb.cube[2], aabb.cube[6]),
    std::make_pair(aabb.cube[3], aabb.cube[7]),
    std::make_pair(aabb.cube[4], aabb.cube[5]),
    std::make_pair(aabb.cube[4], aabb.cube[6]),
    std::make_pair(aabb.cube[5], aabb.cube[7]),
    std::make_pair(aabb.cube[6], aabb.cube[7])
  };
  draw_lines(cube, vp_mat, white);
}
