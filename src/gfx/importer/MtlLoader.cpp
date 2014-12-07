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
    for(auto& name_material_pair: materials) {
      if(current_material.diffuse_map == 0) {
	current_material.diffuse_map = create_texture(1, 1, 1);
	std::cout << current_material.name << " lacks diffuse\n";
      }
      if(current_material.specular_map == 0) {
	current_material.specular_map = create_texture(0, 0, 0);
	std::cout << current_material.name << " lacks specular\n";
      }
      if(current_material.normal_map == 0) {
	current_material.normal_map = create_texture(0, 1, 0);
	std::cout << current_material.name << " lacks normal\n";
      }
      materials[last_material_name] = current_material;
    }
}

GLuint MtlLoader::load_texture(const std::string& path) {
  if(textures.count(path) > 0) {
    return textures[path];
  }
  std::cout << ("load texture: " + path).c_str() << std::endl;
  GLuint tex_2d = SOIL_load_OGL_texture(
      ("assets/" + path).c_str(),
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_MIPMAPS |
      SOIL_FLAG_INVERT_Y
      //SOIL_FLAG_NTSC_SAFE_RGB |
      //SOIL_FLAG_COMPRESS_TO_DXT
      );
  textures[path] = tex_2d;
  return tex_2d;
}

void MtlLoader::handle_tokens(std::vector<std::string> tokens) {
  const char* type = popFirstToken(tokens).c_str();
  if(!strcmp(type, "newmtl")) {
      if(strcmp(last_material_name.c_str(), "")) {
	if(current_material.diffuse_map == 0) {
	  current_material.diffuse_map = create_texture(0, 0, 0);
	  std::cout << current_material.name << " lacks diffuse\n";
	}
	if(current_material.specular_map == 0) {
	  current_material.specular_map = create_texture(0, 0, 0);
	  std::cout << current_material.name << " lacks specular\n";
	}
	if(current_material.normal_map == 0) {
	  current_material.normal_map = create_texture(0, 0, 0.5);
	  std::cout << current_material.name << " lacks normal\n";
	}
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
