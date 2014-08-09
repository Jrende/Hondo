#include "SimpleShader.hpp"
#include "ShaderProgram.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
SimpleShader::SimpleShader(): 
  shader_program("simple"),
  colorID(shader_program.get_uniform("instance.color")),
  mvpMatID(shader_program.get_uniform("instance.mvpMat")),
  diffuse_sampler_id(shader_program.get_uniform("instance.diffuse_sampler"))
{
}

void SimpleShader::operator()() {
  shader_program.use();
}

void SimpleShader::stop() {
  shader_program.stop();
}

void SimpleShader::set_MVP(const glm::mat4& mvpMat) {
  glUniformMatrix4fv(mvpMatID, 1, GL_FALSE, glm::value_ptr(mvpMat));
}

void SimpleShader::set_color(const glm::vec3& color) {
	//std::cout << glm::to_string(color) << std::endl;
  glUniform3f(colorID, color.x, color.y, color.z);
}

void SimpleShader::set_diffuse_sampler(int sampler) {
  glUniform1i(diffuse_sampler_id, sampler);
}
