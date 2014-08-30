#ifndef __HONDO_SHADERPROGRAM_H__
#define __HONDO_SHADERPROGRAM_H__
class ShaderProgram;
#include <string>
#include <vector>
#include <GL/glew.h>
//Todo: Implement copy constructor and copy assignment operator, due to rule of three
class ShaderProgram {
  private:
    const std::string shader_name;
    const GLuint vertex_shader, geometry_shader, fragment_shader, shader_program;
    GLuint compile(GLuint type, std::string source);
  public:
    explicit ShaderProgram(std::string shader_name_);
    ShaderProgram(const ShaderProgram& other);
    ~ShaderProgram();
    void use();
    void stop();
    GLuint get_uniform(std::string name);
};
#endif
