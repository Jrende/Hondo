#ifndef HONDO_FRAMEBUFFERSHADER_HPP
#define HONDO_FRAMEBUFFERSHADER_HPP
class FramebufferShader;
#include "ShaderProgram.hpp"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
class FramebufferShader {
  private:
    ShaderProgram shader_program;
    const GLuint framebuffer_sampler_id;
  public:
    FramebufferShader(); 
    void use_shader();
    void stop();
    void set_framebuffer_sampler(int sampler);
};
#endif
