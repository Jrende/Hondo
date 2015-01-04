#include "FramebufferShader.hpp"
#include "ShaderProgram.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
FramebufferShader::FramebufferShader(): 
  shader_program("fbo"),
  framebuffer_sampler_id(shader_program.get_uniform("sampler"))
{
}

void FramebufferShader::use_shader() {
  shader_program.use();
}

void FramebufferShader::stop() {
  shader_program.stop();
}

void FramebufferShader::set_framebuffer_sampler(int sampler) {
  glUniform1i(framebuffer_sampler_id, sampler);
}
