#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <boost/algorithm/string.hpp>
#include <boost/range.hpp>
#include <boost/tokenizer.hpp>
#include <SOIL.h>

#include "ObjLoaderUtils.hpp"
#include "MtlLoader.hpp"
#include "../../DebugUtils.h"
using namespace boost;
using namespace ObjLoaderUtils;
MtlLoader::MtlLoader(): 
last_material_name("") 
{
}

GLuint create_texture(float r, float g, float b) {
  //Hope 0 isn't a legal value for glGenTextures
  GLuint texture = 0;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  float* data = new float[3];
  data[0] = r; data[1] = g; data[2] = b;
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_FLOAT, &data[0]);
  glBindTexture(GL_TEXTURE_2D, 0);
  return texture;
}

void MtlLoader::load_materials(const std::string& path) {
  std::ifstream file(path);
  if(!file.is_open()) {
    printf("Failed to open %s!", path.c_str());
    exit(EXIT_FAILURE);
  }
  std::string line;
  char_separator<char> space_sep(" ");
  while(getline(file, line)) {
    boost::trim(line);
    std::vector<std::string> tokens;
    boost::split(tokens, line, boost::is_any_of(" "));
    //Might make parsing faster.
    //tokens.reserve(4);
    if(tokens.size() > 0) {
      handle_tokens(tokens);
    }
  }
  for(auto& str_mat_pair: materials) {
    auto& mat = str_mat_pair.second;
    if(!mat.diffuse_map) mat.diffuse_map = create_texture(1, 1, 1);
    if(!mat.specular_map) mat.specular_map = create_texture(0, 0, 0);
    if(!mat.normal_map) mat.normal_map = create_texture(0.5, 0.5, 1);
    if(!mat.mask) mat.mask = create_texture(1, 1, 1);
  }
}

GLuint MtlLoader::load_texture(const std::string& path) {
  std::string fixed_path = path;
  boost::replace_all(fixed_path, "//", "/");
  boost::replace_all(fixed_path, "\\", "/");
  std::cout << "load texture: assets/" << fixed_path;
  GLuint tex_2d = SOIL_load_OGL_texture(
      ("assets/" + fixed_path).c_str(),
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y |
      SOIL_FLAG_TEXTURE_REPEATS
      );
  if(tex_2d == 0) {
    std::cout << " <--- Failed!\n";
  } else {
    std::cout << "\n";
  }
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
  } else if(!strcmp(type, "map_d")) {
    current_material.mask = load_texture(tokens[0]);
  }
  materials[last_material_name] = current_material;
}
