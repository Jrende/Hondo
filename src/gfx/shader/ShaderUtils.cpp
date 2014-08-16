#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>

namespace ShaderUtils {
  inline std::string get_shader_type_string(GLuint type) {
    if(type == GL_FRAGMENT_SHADER) {
      return "frag";
    } else if(type == GL_GEOMETRY_SHADER) {
      return "geom";
    } else if(type == GL_VERTEX_SHADER) {
      return "vert";
    } else {
      return "unknown";
    }
  }

  inline void print_errorlog(GLuint shader) {
    GLint length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
    GLchar *info = new GLchar[length + 1];
    glGetShaderInfoLog(shader, length, NULL, info);
    std::cout << "infolog: " << info << std::endl;
    delete[] info;
  }

  inline std::string load_file(std::string path) {
    std::ifstream file;
    file.open(path, std::ios::in);
    if(!file.is_open()) {
      printf("Failed to open %s!\n", path.c_str());
      return "";
    }
    std::string line;
    std::stringbuf src;
    while(getline(file, line)) {
      src.sputn(line.c_str(), line.size());
      src.sputc('\n');
    }
    file.close();
    return src.str();
  }
}
