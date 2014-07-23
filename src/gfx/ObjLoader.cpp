#include "ObjLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include "ObjLoaderUtils.cpp"

using namespace boost;
using namespace ObjLoaderUtils;
ObjLoader::ObjLoader(std::string path) {
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
      handleTokens(tokens);
      std::cout << std::endl;
    }
    file.close();
}

void ObjLoader::createFace(const std::vector<std::string>& face) {
    char_separator<char> slash_sep("/");
    for(auto& vertTokens: face) {
      tokenizer<char_separator<char> > tokenizer(vertTokens, slash_sep);
      std::vector<int> vert;
      for(auto& t: tokenizer)
	vert.push_back(atoi(t.c_str()) - 1);
      for(auto& pos: posList[vert[0]]) 
	vertexBuffer.push_back(pos);
      for(auto& uv: uvList[vert[1]]) 
	vertexBuffer.push_back(uv);
      for(auto& normal: normalList[vert[2]]) 
	vertexBuffer.push_back(normal);
    }
}

//std::cout << vert[0] << ", " << vert[1] << ", " << vert[2] << std::endl;
void ObjLoader::handleTokens(std::vector<std::string> tokens) {
  const char* type = popFirstToken(tokens).c_str();
  if(!strcmp(type, "v")) {
    auto vert = toFloatArray<3>(tokens);
    posList.push_back(vert);
  } else if(!strcmp(type, "vt")) {
    auto vert = toFloatArray<2>(tokens);
    uvList.push_back(vert);
  } else if(!strcmp(type, "vn")) {
    auto vert = toFloatArray<3>(tokens);
    normalList.push_back(vert);
  } else if(!strcmp(type, "f")) {
    createFace(tokens);
  }
}

std::vector<float> ObjLoader::getVertices() {
  return {};
}
