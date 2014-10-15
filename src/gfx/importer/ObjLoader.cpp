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

std::vector<std::shared_ptr<Mesh>> ObjLoader::load_meshes(const std::string& path) {
  std::map<std::string, int> loaded_vertices;
  std::map<std::shared_ptr<Mesh>, std::vector<float>> vertices_per_mesh;
  std::map<std::shared_ptr<Mesh>, std::vector<unsigned int>> indices_per_mesh;
  std::vector<std::shared_ptr<Mesh>> meshes;


  ifstream file(path);
  if(!file.is_open()) {
    cout << "Unable to open " << path;
  }
  string line;
  
  vector<float> pos;
  vector<float> uvs;
  vector<float> normals;

  std::shared_ptr<Mesh> current_mesh = std::make_shared<Mesh>();
  current_mesh->name = "initial";
  unsigned int vertices_count = 0;
  unsigned int last_index = 0;
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
      current_mesh->count = vertices_count;
      vertices_count = 0;
    } else if(!strcmp(tokens[0].c_str(), "usemtl")) {
      //mesh->material = mtl_loader.load_material(tokens[1]);
    } else if(!strcmp(tokens[0].c_str(), "f")) {
      Face face;
      for(auto& v: tokens) {
	if(!strcmp(v.c_str(), "f")) continue;
	trim(v);
	if(v.size() == 0) continue;
	Vertex vertex;
	vertices_count++;
	if(loaded_vertices.count(v) > 0) {
	  indices_per_mesh[current_mesh].push_back(loaded_vertices[v]);
	  vertex.is_indexed = true;
	}
	vector<string> tokenizer;
	split(tokenizer, v, is_any_of("/"));
	std::vector<int> vert;
	for(const auto& t: tokenizer)
	  vert.push_back(atoi(t.c_str()) - 1);
	for(int j = 0; j < 3; j++)
	  vertex.pos[j] = pos[vert[0]*3 + j];
	for(int j = 0; j < 2; j++)
	  vertex.uv[j] = uvs[vert[1]*2 + j];
	for(int j = 0; j < 3; j++)
	  vertex.normal[j] = normals[vert[2]*3 + j];
	face.verts.push_back(vertex);
	if(!vertex.is_indexed) {
	  loaded_vertices[v] = last_index;
	  indices_per_mesh[current_mesh].push_back(last_index);
	  last_index++;
	}
      }
      calcTangent(face);
      for(const auto& vert: face.verts) {
	if(vert.is_indexed) {
	  continue;
	}
	for(const auto& val: vert.pos)
	  vertices_per_mesh[current_mesh].push_back(val);
	for(const auto& val: vert.uv)
	  vertices_per_mesh[current_mesh].push_back(val);
	for(const auto& val: vert.normal)
	  vertices_per_mesh[current_mesh].push_back(val);
	for(const auto& val: vert.tangent)
	  vertices_per_mesh[current_mesh].push_back(val);
	for(const auto& val: vert.bitangent)
	  vertices_per_mesh[current_mesh].push_back(val);
      }
    }
  }
  for(auto& mesh: meshes) {
    mesh->vertex_array = std::make_shared<VertexArray>(VertexArray(
	vertices_per_mesh[mesh],
	indices_per_mesh[mesh],
	mesh->count,
	{3,2,3,3,3}
    ));
  }
  return meshes;
}
