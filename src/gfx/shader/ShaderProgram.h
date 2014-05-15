#ifndef __HONDO_SHADER_H__
#define __HONDO_SHADER_H__
class ShaderProgram;
#include <string>
#include <vector>
#include <GL/glew.h>
using namespace std;
class ShaderProgram {
  private:
    GLuint vertex_shader, fragment_shader, shader_program;
    const string shader_name;
    string load_file(string path);
    GLuint compile(GLuint type, string source);
    void printErrorlog(GLuint shader);
  public:
    ShaderProgram(string _shader_name);
    ~ShaderProgram();
};
#endif
