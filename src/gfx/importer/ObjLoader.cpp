#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <boost/algorithm/string.hpp>
#include <boost/range.hpp>
#include <boost/tokenizer.hpp>

#include "ObjLoader.hpp"
#include "ObjLoaderUtils.hpp"

using namespace boost;
using namespace ObjLoaderUtils;
using std::cout;
ObjLoader::ObjLoader():
  vertex_array(),
  index_array()
{
  
}

void ObjLoader::load_file(const std::string& path) {
  std::ifstream file(path);
  if(!file.is_open()) {
    printf("Failed to open %s!", path.c_str());
    exit(EXIT_FAILURE);
  }
  std::string line;
  char_separator<char> space_sep(" ");
  while(getline(file, line)) {
    boost::trim(line);
    if(line.size() > 0) {
      tokenizer<char_separator<char> > st(line, space_sep);
      std::vector<std::string> tokens;
      //Might make parsing faster.
      //tokens.reserve(4);
      for(auto& token: st) {
	tokens.push_back(token);
      }
      handleTokens(tokens);
    }
  }
}

void ObjLoader::handleTokens(std::vector<std::string>& tokens) {
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
    if(tokens.size() == 3) {
      createFace({tokens[0], tokens[1], tokens[2]});
    } else if(tokens.size() == 4) {
      createFace({tokens[0], tokens[2], tokens[3]});
      createFace({tokens[0], tokens[1], tokens[2]});
    }
  }
}

  template<long long unsigned int n>
    void printVec(std::array<float, n> vec) {
      for(const auto& v: vec)
	std::cout << v << ", ";
      std::cout << "\n";
    }

void ObjLoader::createFace(const std::vector<std::string>& face_string) {
  char_separator<char> slash_sep("/");
  Face face;
  face.verts.resize(3);
  for(auto i = 0u; i < face_string.size(); i++) {
    const auto& vertTokens = face_string[i];
    //Is the vertex already loaded to the buffer?
    Vertex vertex;
    if(loaded_vertices_map.count(vertTokens) > 0) {
      index_array.push_back(loaded_vertices_map[vertTokens]);
      vertex.isIndexed = true;
    }
    tokenizer<char_separator<char> > tokenizer(vertTokens, slash_sep);
    std::vector<int> vert;
    for(const auto& t: tokenizer)
      vert.push_back(atoi(t.c_str()) - 1);
    for(int j = 0; j < 3; j++)
      vertex.pos[j] = posList[vert[0]][j];
    for(int j = 0; j < 2; j++)
      vertex.uv[j] = uvList[vert[1]][j];
    for(int j = 0; j < 3; j++)
      vertex.normal[j] = normalList[vert[2]][j];
    face.verts[i] = vertex;

    if(!vertex.isIndexed) {
      loaded_vertices_map[vertTokens] = last_index;
      index_array.push_back(last_index);
      last_index++;
    }
  }

  calcTangent(face);
  for(const auto& vert: face.verts) {
    if(vert.isIndexed) {
      continue;
    }
    for(const auto& val: vert.pos)
      vertex_array.push_back(val);
    for(const auto& val: vert.uv)
      vertex_array.push_back(val);
    for(const auto& val: vert.normal)
      vertex_array.push_back(val);
    for(const auto& val: vert.tangent)
      vertex_array.push_back(val);
    for(const auto& val: vert.bitangent)
      vertex_array.push_back(val);
  }
}

std::vector<std::string> get_tokens(std::string line) {
  static char_separator<char> space_sep(" ");
  boost::trim(line);
  tokenizer<char_separator<char> > st(line, space_sep);
  std::vector<std::string> tokens;
  //Might make parsing faster.
  //tokens.reserve(4);
  for(auto& token: st) {
    tokens.push_back(token);
  }
  return tokens;
}

void ObjLoader::preload(const std::string& filename) {
  file_list.push_back(filename);
  int current_vertex_count = 0;
  std::ifstream file(filename);
  if(!file.is_open()) {
    printf("Failed to open %s!", filename.c_str());
    exit(EXIT_FAILURE);
  }
  std::string line;

  Mesh current_mesh;
  current_mesh.name = "initial";
  current_mesh.start = vertex_count;
  while(getline(file, line)) {
    auto tokens = get_tokens(line);
    if(tokens.size() == 0) {
      continue;
    }

    if(!strcmp(tokens[0].c_str(), "g")) {
      current_mesh.end = vertex_count + current_mesh.start;
      cout << "end: " << current_mesh.end << "\n";
      if((current_mesh.start - current_mesh.end) > 0) {
	mesh_list.push_back(current_mesh); 
      }

      current_mesh = Mesh();
      current_mesh.name = tokens[1];
      current_mesh.start = current_vertex_count + vertex_count;
    } else if(!strcmp(tokens[0].c_str(), "f")) {
      if(tokens.size() == 4) {
	current_vertex_count += 3;
      } else if(tokens.size() == 5) {
	current_vertex_count += 6;
      }
    } else if(!strcmp(tokens[0].c_str(), "mtllib")) {
      mtl_loader.load_materials("assets/" + tokens[1]);
    } else if(!strcmp(tokens[0].c_str(), "usemtl")) {
      current_mesh.material = mtl_loader.materials[tokens[1]];
    }
  }
  current_mesh.end = current_vertex_count + current_mesh.start;
  mesh_list.push_back(current_mesh);

  vertex_count += current_vertex_count;
}

void ObjLoader::load_preloaded_data() {
  std::cout << "Reserving " << vertex_count << " for vertex array" << std::endl;
  vertex_array.reserve(vertex_count);
  last_index_count = 0;
  for(const auto& file: file_list) {
    load_file(file);
    //loaded_vertices.clear();
    loaded_vertices_map.clear();
    posList.clear();
    uvList.clear();
    normalList.clear();
    last_index_count = last_index;
  }
  /*
  for(const auto& p: (*vertex_array)) {
    std::cout << p << ", ";
  }
  */
}
