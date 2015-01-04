#ifndef HONDO_DEPTHSHADER_HPP
#define HONDO_DEPTHSHADER_HPP
class DepthShader;
#include "ShaderProgram.hpp"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
class DepthShader {
  private:
    ShaderProgram shader_program;
    const GLuint mvpMatID;
  public:
    DepthShader(); 
    void use_shader();
    void stop();
    void set_mvp_mat(const glm::mat4& mvpMat);
};
#endif
