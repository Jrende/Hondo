#include "ShaderProgram.hpp"
#include "ShaderUtils.cpp"

ShaderProgram::ShaderProgram(std::string shader_name_):
  shader_name(shader_name_),
  vertex_shader(
      compile(
	GL_VERTEX_SHADER,
	ShaderUtils::load_file("glsl/" + shader_name_ + ".vert")
      )
  ),
  fragment_shader(
      compile(
	GL_FRAGMENT_SHADER,
	ShaderUtils::load_file("glsl/" + shader_name_ + ".frag")
      )
  ),
  shader_program(glCreateProgram())
{
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);
}

ShaderProgram::ShaderProgram(const ShaderProgram& other): ShaderProgram(other.shader_name) {}

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

void ShaderProgram::use() {
  glUseProgram(shader_program);
}

void ShaderProgram::stop() {
  glUseProgram(0);
}

GLuint ShaderProgram::get_uniform(std::string name) {
  return glGetUniformLocation(shader_program, name.c_str());
}

GLuint ShaderProgram::compile(GLuint type, std::string source) {
  int shader = glCreateShader(type);
  if(!shader) {
    std::cout << "Error creating " << shader_name << ".frag" << std::endl;
    exit(EXIT_FAILURE);
  }
  const char *src = source.c_str();
  glShaderSource(shader, 1, &src, NULL);
  glCompileShader(shader);
  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if(status == GL_FALSE) {
    std::cout << "Error in " << shader_name << "." << ShaderUtils::get_shader_type_string(type) << "  Log:" << std::endl;
    ShaderUtils::print_errorlog(shader);
    exit(EXIT_FAILURE);
  }
  return shader;
}
