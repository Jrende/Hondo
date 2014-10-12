#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <boost/algorithm/string.hpp>

#include "ObjLoader.hpp"
#include "ObjLoaderUtils.hpp"

using namespace boost;
using namespace ObjLoaderUtils;
using namespace std;
ObjLoader::ObjLoader() {

}

std::vector<Mesh> ObjLoader::load_meshes(const std::string& path) {
  ifstream file(path);
  if(!file.is_open()) {
    cout << "Unable to open " << path;
  }
  string line;
  
  vector<float> pos;
  vector<float> uvs;
  vector<float> normals;
  vector<float> vertices;
  std::shared_ptr<Mesh> current_mesh = std::make_shared<Mesh>();
  current_mesh->name = "initial";
  while(getline(file, line)) {
    trim(line);
    if(line.size() == 0) continue;
    vector<string> tokens;
    split(tokens, line, is_any_of(" "));

    if(!strcmp(tokens[0].c_str(), "v")) {
      for(int i = 0; i < 3; i++)
	pos.push_back(strtof(tokens[i + 1].c_str(), NULL));
    } else if(!strcmp(tokens[0].c_str(), "vt")) {
      for(int i = 0; i < 2; i++)
	uvs.push_back(strtof(tokens[i + 1].c_str(), NULL));
    } else if(!strcmp(tokens[0].c_str(), "vn")) {
      for(int i = 0; i < 3; i++)
	normals.push_back(strtof(tokens[i + 1].c_str(), NULL));
    } else if(
	!strcmp(tokens[0].c_str(), "o") ||
	!strcmp(tokens[0].c_str(), "g")) {
      if(current_mesh->count > 0) 
	meshes.push_back(current_mesh);
      current_mesh = std::make_shared<Mesh>();
      current_mesh->name = tokens[1];
    } else if(!strcmp(tokens[0].c_str(), "usemtl")) {
      //mesh->material = mtl_loader.load_material(tokens[1]);
    } else if(!strcmp(tokens[0].c_str(), "f")) {
      Face face;
      for(auto& v: tokens) {
	trim(v);
	Vertex vertex;
	if(v.size() == 0) continue;
	if(loaded_vertices.count(v) > 0) {
	  indices_per_mesh[current_mesh].push_back(loaded_vertices[v]);
	  vertex.is_indexed = true;
	}

      }
      split(tokens, line, is_any_of(" "));
    }
  }
}
