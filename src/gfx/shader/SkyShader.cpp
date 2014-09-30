#include "SkyShader.hpp"
#include "ShaderProgram.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
SkyShader::SkyShader(): 
  shader_program("SkyShader"),
  mvpMatID(shader_program.get_uniform("mvpMatrix")),
  modelMatID(shader_program.get_uniform("modelMatrix"))
{
}

void SkyShader::operator()() {
  shader_program.use();
}

void SkyShader::stop() {
  shader_program.stop();
}

void SkyShader::set_mvp_mat(const glm::mat4& mvpMat) {
  glUniformMatrix4fv(mvpMatID, 1, GL_FALSE, glm::value_ptr(mvpMat));
}

void SkyShader::set_model_mat(const glm::mat4& mvpMat) {
  glUniformMatrix4fv(modelMatID, 1, GL_FALSE, glm::value_ptr(mvpMat));
}
