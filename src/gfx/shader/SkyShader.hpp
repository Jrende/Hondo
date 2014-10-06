#ifndef HONDO_SKYSHADER_HPP
#define HONDO_SKYSHADER_HPP
class SkyShader;
#include "ShaderProgram.hpp"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
class SkyShader {
  private:
    ShaderProgram shader_program;
    const GLuint mvpMatID;
    const GLuint modelMatID;
  public:
    SkyShader(); 
    void operator()();
    void stop();
    void set_mvp_mat(const glm::mat4& mvpMat);
    void set_model_mat(const glm::mat4& mvpMat);
};
#endif
