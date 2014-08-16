#include "DebugShader.hpp"
#include "ShaderProgram.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
DebugShader::DebugShader(): 
  shader_program("DebugShader"),
  pos_id(shader_program.get_uniform("pos")),
  color_id(shader_program.get_uniform("color")),
  mvp_mat_id(shader_program.get_uniform("mvp_mat")),
  mode_id(shader_program.get_uniform("mode"))
{
}

void DebugShader::operator()() {
  shader_program.use();
}

void DebugShader::stop() {
  shader_program.stop();
}

void DebugShader::set_MVP(const glm::mat4& mvpMat) {
  glUniformMatrix4fv(mvp_mat_id, 1, GL_FALSE, glm::value_ptr(mvpMat));
}

void DebugShader::set_pos(const glm::vec3& pos) {
  glUniform3f(pos_id, pos.x, pos.y, pos.z);
}

void DebugShader::set_color(const glm::vec3& color) {
  glUniform3f(color_id, color.x, color.y, color.z);
}

void DebugShader::set_mode(const float& mode) {
  glUniform1f(color_id, mode);
}

