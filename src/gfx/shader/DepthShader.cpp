#include "DepthShader.hpp"
#include "ShaderProgram.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
DepthShader::DepthShader(): 
  shader_program("depth"),
  mvpMatID(shader_program.get_uniform("mvp_mat"))
{
}

void DepthShader::use_shader() {
  shader_program.use();
}

void DepthShader::stop() {
  shader_program.stop();
}

void DepthShader::set_mvp_mat(const glm::mat4& mvpMat) {
  glUniformMatrix4fv(mvpMatID, 1, GL_FALSE, glm::value_ptr(mvpMat));
}
