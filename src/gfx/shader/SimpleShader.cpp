#include "SimpleShader.h"
#include "ShaderProgram.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
SimpleShader::SimpleShader(): 
  shader_program("simple"),
  colorID(shader_program.get_uniform("color")),
  mvpMatID(shader_program.get_uniform("mvpMat"))
{
}

void SimpleShader::operator()() {
  shader_program.use();
}

void SimpleShader::stop() {
  shader_program.stop();
}

void SimpleShader::set_MVP(glm::mat4 mvpMat) {
  glUniformMatrix4fv(mvpMatID, 1, GL_FALSE, glm::value_ptr(mvpMat));
}
void SimpleShader::set_color(glm::vec3 color) {
	//std::cout << glm::to_string(color) << std::endl;
  glUniform3f(colorID, color.x, color.y, color.z);
}
