#include "LineShader.hpp"
#include "ShaderProgram.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
LineShader::LineShader(): 
  shader_program("LineShader"),
  from_id(shader_program.get_uniform("from")),
  to_id(shader_program.get_uniform("to")),
  color_id(shader_program.get_uniform("color")),
  mvp_mat_id(shader_program.get_uniform("mvp_mat"))
{
}

void LineShader::operator()() {
  shader_program.use();
}

void LineShader::stop() {
  shader_program.stop();
}

void LineShader::set_MVP(const glm::mat4& mvpMat) {
  glUniformMatrix4fv(mvp_mat_id, 1, GL_FALSE, glm::value_ptr(mvpMat));
}

void LineShader::set_from(const glm::vec3& from) {
  glUniform3f(from_id, from.x, from.y, from.z);
}

void LineShader::set_to(const glm::vec3& to) {
  glUniform3f(to_id, to.x, to.y, to.z);
}

void LineShader::set_color(const glm::vec3& color) {
  glUniform3f(color_id, color.x, color.y, color.z);
}

