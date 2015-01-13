#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>

#include "ObjLoader.hpp"

using namespace boost;
using namespace ObjLoaderUtils;
using namespace std;

//Might be source of problems
void ObjLoader::create_vertex(const std::string& vertex_string, Vertex& vertex) {
  vector<string> tokenizer;
  split(tokenizer, vertex_string, is_any_of("/"));
  std::vector<int> vert;
  for(const auto& t: tokenizer)
    vert.push_back(atoi(t.c_str()) - 1);
  for(int j = 0; j < 3; j++)
    vertex.pos[j] = pos[vert[0]*3 + j];
  for(int j = 0; j < 2; j++)
    vertex.uv[j] = uvs[vert[1]*2 + j];
  for(int j = 0; j < 3; j++)
    vertex.normal[j] = normals[vert[2]*3 + j];
}

void ObjLoader::preload_file(const std::string& path) {
  paths.push_back(path);

  loaded_vertices.clear();
  pos.clear();
  uvs.clear();
  normals.clear();

  ifstream file(path);
  if(!file.is_open()) {
    cout << "Unable to open " << path;
  }
  string line;
  
  current_mesh = Mesh();

  last_index = 0;
  while(getline(file, line)) {
    trim(line);
    if(line.size() == 0) continue;
    vector<string> tokens;
    split_regex(tokens, line, regex("\\s+"));

    if(!strcmp(tokens[0].c_str(), "#")) {
      continue;
    } else if(!strcmp(tokens[0].c_str(), "v")) {
      for(int i = 0; i < 3; i++)
	pos.push_back(strtof(tokens[i + 1].c_str(), NULL));
    } else if(!strcmp(tokens[0].c_str(), "vt")) {
      for(int i = 0; i < 2; i++)
	uvs.push_back(strtof(tokens[i + 1].c_str(), NULL));
    } else if(!strcmp(tokens[0].c_str(), "vn")) {
      for(int i = 0; i < 3; i++)
	normals.push_back(strtof(tokens[i + 1].c_str(), NULL));
    } else if(!strcmp(tokens[0].c_str(), "o") || !strcmp(tokens[0].c_str(), "g")) {
      if(current_mesh.vertex_count > 0) 
	meshes_per_file[path].push_back(current_mesh);
      current_mesh = Mesh(indices_count, vertices_count, tokens[1]);
      last_index = 0;
    } else if(!strcmp(tokens[0].c_str(), "mtllib")) {
      mtl_loader.load_materials("assets/" + tokens[1]);
    } else if(!strcmp(tokens[0].c_str(), "usemtl")) {
      if(current_mesh.vertex_count > 0) 
	meshes_per_file[path].push_back(current_mesh);
      current_mesh = Mesh(indices_count, vertices_count, tokens[1]);
      last_index = 0;
      current_mesh.material = mtl_loader.materials[tokens[1]];
    } else if(!strcmp(tokens[0].c_str(), "f")) {
      std::vector<std::string> quad_face{tokens[1], tokens[2], tokens[3]};
      create_face(quad_face);
      //If face is quad
      if(tokens.size() == 5) {
	std::vector<std::string> quad_face{tokens[1], tokens[3], tokens[4]};
	create_face(quad_face);
      }
    }
  }
  meshes_per_file[path].push_back(current_mesh);
}

void ObjLoader::create_face(std::vector<std::string> tokens) {
  Face face;
  for(auto& v: tokens) {
    if(!strcmp(v.c_str(), "f")) continue;
    trim(v);
    if(v.size() == 0) continue;
    Vertex vertex;
    if(loaded_vertices.count(v) > 0) {
      add_vertex_to_indices(loaded_vertices[v]);
      vertex.is_indexed = true;
    }
    create_vertex(v, vertex);
    face.verts.push_back(vertex);
    if(!vertex.is_indexed) {
      loaded_vertices[v] = last_index;
      add_vertex_to_indices(last_index);
      last_index++;
    }
  }
  calcTangent(face);
  add_face(face);
}

void ObjLoader::add_vertex_to_indices(int index) {
  index_buffer.push_back(index);
  current_mesh.index_count++;
  indices_count++;
}

const std::vector<Mesh>& ObjLoader::get_meshes(const std::string& path) {
  return meshes_per_file[path];
}

void ObjLoader::add_face(Face& face) {
  for(const auto& vert: face.verts) {
    if(vert.is_indexed) {
      continue;
    }
    current_mesh.vertex_count++;
    vertices_count++;
    for(const auto& val: vert.pos)
      vertex_buffer.push_back(val);
    for(const auto& val: vert.uv)
      vertex_buffer.push_back(val);
    for(const auto& val: vert.normal)
      vertex_buffer.push_back(val);
    for(const auto& val: vert.tangent)
      vertex_buffer.push_back(val);
  }
}

void ObjLoader::load_files() {
  for(auto& filename_mesh_pair: meshes_per_file) {
    for(auto& mesh: filename_mesh_pair.second) {
      auto vertex_array = std::make_shared<VertexArray>(
	std::vector<float>(
	    vertex_buffer.begin() + mesh.vertex_start * 11,
	    vertex_buffer.begin() + ((mesh.vertex_start + mesh.vertex_count) * 11)),
	std::vector<unsigned int>(
	    index_buffer.begin() + mesh.index_start,
	    index_buffer.begin() + (mesh.index_start + mesh.index_count)),
	mesh.index_count,
	std::vector<unsigned int>({3, 2, 3, 3})
      );
      vertex_array_store.push_back(vertex_array);
      mesh.vertex_array = (*vertex_array_store.back());
    }
    std::cout << "file " << filename_mesh_pair.first << " loaded.\n";
  }
}
