#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <boost/algorithm/string.hpp>
#include <boost/range.hpp>
#include <boost/tokenizer.hpp>
#include <SOIL.h>
#include <GL/glew.h>

#include "ObjLoaderUtils.cpp"
#include "MtlLoader.hpp"
using namespace boost;
using namespace ObjLoaderUtils;
MtlLoader::MtlLoader(): 
last_material_name("") 
{
}
void MtlLoader::load_materials(const std::string& path) {
    std::ifstream file;
    file.open(path, std::ios::in);
    if(!file.is_open()) {
      printf("Failed to open %s!", path.c_str());
      exit(EXIT_FAILURE);
    }
    std::string line;
    char_separator<char> space_sep(" ");
    while(getline(file, line)) {
      boost::trim(line);
      tokenizer<char_separator<char> > st(line, space_sep);
      std::vector<std::string> tokens;
      //Might make parsing faster.
      //tokens.reserve(4);
      for(auto& token: st) {
	tokens.push_back(token);
      }
      if(tokens.size() > 0) {
	handle_tokens(tokens);
      }
    }
    file.close();
}

GLuint load_texture(const std::string& path) {
  std::cout << ("load texture: " + path).c_str() << std::endl;
  GLuint tex_2d = SOIL_load_OGL_texture(
      ("assets/" + path).c_str(),
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_MIPMAPS |
      SOIL_FLAG_INVERT_Y |
      SOIL_FLAG_NTSC_SAFE_RGB |
      SOIL_FLAG_COMPRESS_TO_DXT
      );
  return tex_2d;
}

void MtlLoader::handle_tokens(std::vector<std::string> tokens) {
  const char* type = popFirstToken(tokens).c_str();
  if(!strcmp(type, "newmtl")) {
      if(strcmp(last_material_name.c_str(), "")) {
	materials[last_material_name] = current_material;
      }
      last_material_name = tokens[0];
      current_material = Material(tokens[0]);
  } else if(!strcmp(type, "map_Kd")) {
    current_material.diffuse_map = load_texture(tokens[0]);

    GLfloat fLargest;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);
  } else if(!strcmp(type, "map_Ns")) {
    current_material.specular_map = load_texture(tokens[0]);
  } else if(!strcmp(type, "map_bump")) {
    current_material.normal_map = load_texture(tokens[0]);
  }
  materials[last_material_name] = current_material;
}
