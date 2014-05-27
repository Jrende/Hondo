#include "SimpleShader.h"
#include "ShaderProgram.h"
#include <glm/gtc/type_ptr.hpp>
SimpleShader::SimpleShader(): 
  shader_program("simple"),
  colorID(shader_program.getUniform("color")),
  modelMatrixID(shader_program.getUniform("modelMatrix"))
{

}

void SimpleShader::operator()() {
  shader_program.use();
}

void SimpleShader::stop() {
  shader_program.stop();
}

void SimpleShader::setModelMatrix(glm::mat4 modelMatrix) {
  glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}
