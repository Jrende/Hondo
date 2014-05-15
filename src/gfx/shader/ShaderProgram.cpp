#include "ShaderProgram.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
ShaderProgram::ShaderProgram(string _shader_name): shader_name(_shader_name) {
  cout << "Loading vert" << endl;
  string vert_src = load_file("glsl/" + shader_name + ".vert");
  vertex_shader = compile(GL_VERTEX_SHADER, vert_src);

  cout << "Loading frag" << endl;
  string frag_src = load_file("glsl/" + shader_name + ".frag");
  fragment_shader = compile(GL_FRAGMENT_SHADER, frag_src);

  cout << "Create program" << endl;
  shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);
}

ShaderProgram::~ShaderProgram() {
  //Might be a good idea to detach shader before deleting.
  if(shader_program) {
    glDeleteProgram(shader_program);
  }

  if(fragment_shader) {
    glDeleteShader(fragment_shader);
  }

  if(vertex_shader) {
    glDeleteShader(vertex_shader);
  }
}

GLuint ShaderProgram::compile(GLuint type, string source) {
  cout << "create shader" << endl;
  int shader = glCreateShader(type);
  cout << "created shader" << endl;
  if(shader) {
    cout << "Error creating shader!" << endl;
    exit(EXIT_FAILURE);
  }
  cout << "preCompile" << endl;
  const char *src = source.c_str();
  glShaderSource(shader, 1, &src, NULL);
  glCompileShader(shader);
  cout << "postCompile" << endl;
  delete[] src;
  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if(status == GL_FALSE) {
    printErrorlog(shader);
    exit(EXIT_FAILURE);
  }
  return shader;
}

void ShaderProgram::printErrorlog(GLuint shader) {
    GLint length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
    GLchar *info = new GLchar[length + 1];
    glGetShaderInfoLog(shader, length, NULL, info);
    cout << "infolog: " << info;
    delete[] info;
}

string ShaderProgram::load_file(string path) {
  ifstream shader_file;
  shader_file.open(path, ios::in);
  if(!shader_file.is_open()) {
    printf("Failed to open %s!", path.c_str());
    exit(EXIT_FAILURE);
  }
  string line;
  stringbuf src;
  while(getline(shader_file, line)) {
    src.sputn(line.c_str(), line.size());
    src.sputc('\n');
  }
  shader_file.close();
  return src.str();
}
