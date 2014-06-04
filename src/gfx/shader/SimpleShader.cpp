#include "SimpleShader.h"
#include "ShaderProgram.h"
#include <glm/gtc/type_ptr.hpp>
SimpleShader::SimpleShader(): 
  shader_program("simple"),
  colorID(shader_program.getUniform("color")),
  mvpMatID(shader_program.getUniform("mvpMat"))
{
  
}

void SimpleShader::operator()() {
  shader_program.use();
}

void SimpleShader::stop() {
  shader_program.stop();
}

void SimpleShader::setMVP(glm::mat4 mvpMat) {
  glUniformMatrix4fv(mvpMatID, 1, GL_FALSE, glm::value_ptr(mvpMat));
}
