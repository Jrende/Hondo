#ifndef __HONDO_SIMPLESHADER_H__
#define __HONDO_SIMPLESHADER_H__
class SimpleShader;
#include "ShaderProgram.hpp"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
class SimpleShader {
  private:
    ShaderProgram shader_program;
    const GLuint colorID;
    const GLuint mvpMatID;
    const GLuint diffuse_sampler_id;
  public:
    SimpleShader(); 
    void operator()();
    void stop();
    void set_MVP(const glm::mat4& mvpMat);
    void set_color(const glm::vec3& color);
    void set_diffuse_sampler(int sampler);
};
#endif
