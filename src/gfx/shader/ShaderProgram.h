#ifndef __HONDO_SHADER_H__
#define __HONDO_SHADER_H__
class ShaderProgram;
#include <string>
#include <vector>
#include <GL/glew.h>
using namespace std;
//Todo: Implement copy constructor and copy assignment operator, due to rule of three
class ShaderProgram {
  private:
    const string shader_name;
    const GLuint vertex_shader, fragment_shader, shader_program;
    GLuint compile(GLuint type, string source);
  public:
    explicit ShaderProgram(string shader_name_);
    ShaderProgram(const ShaderProgram& other);
    ~ShaderProgram();
    void use();
    void stop();
    GLuint getUniform(string name);
};
#endif
