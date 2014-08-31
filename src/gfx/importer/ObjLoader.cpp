#include <iostream>
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
ObjLoader::ObjLoader():
  last_index_count(0), 
  last_index(0), 
  last_end(0), 
  last_name(""),
  last_material(),
  vertex_count(0), 
  vertex_array(std::shared_ptr<std::vector<float>>(new std::vector<float>())),
  index_array(std::shared_ptr<std::vector<unsigned int>>(new std::vector<unsigned int>()))
{
  
}

void ObjLoader::load_file(const std::string& path) {
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
  file.close();
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

void ObjLoader::createFace(const std::vector<std::string>& face_string) {
  char_separator<char> slash_sep("/");
  Face face;
  for(int i = 0; i < face_string.size(); i++) {
    const auto& vertTokens = face_string[i];
    //Is the vertex already loaded to the buffer?
    if(loaded_vertices_map.count(vertTokens) > 0) {
      index_array->push_back(loaded_vertices_map[vertTokens]);
      continue;
    }
    tokenizer<char_separator<char> > tokenizer(vertTokens, slash_sep);
    std::vector<int> vert;
    for(const auto& t: tokenizer) {
      vert.push_back(atoi(t.c_str()) - 1);
    }
    Vertex vertex;
    for(int j = 0; j < 3; j++)
      vertex.pos[j] = posList[vert[0]][j];
    for(int j = 0; j < 2; j++)
      vertex.uv[j] = uvList[vert[1]][j];
    for(int j = 0; j < 3; j++)
      vertex.normal[j] = normalList[vert[2]][j];
    face.verts.push_back(vertex);

    loaded_vertices_map[vertTokens] = last_index;
    index_array->push_back(last_index);
    last_index++;
  }

  calcTangent(face);
  for(const auto& vert: face.verts) {
    for(const auto& val: vert.pos)
      vertex_array->push_back(val);
    for(const auto& val: vert.uv)
      vertex_array->push_back(val);
    for(const auto& val: vert.normal)
      vertex_array->push_back(val);
    //for(const auto& val: vert.tangent)
      //vertex_array->push_back(val);
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

std::vector<Mesh> ObjLoader::preload(const std::string& filename) {
  file_list.push_back(filename);
  std::vector<Mesh> ret;
  std::ifstream file;
  int current_vertex_count = 0;
  file.open(filename, std::ios::in);
  if(!file.is_open()) {
    printf("Failed to open %s!", filename.c_str());
    exit(EXIT_FAILURE);
  }
  std::string line;
  while(getline(file, line)) {
    auto tokens = get_tokens(line);
    if(tokens.size() == 0) {
      continue;
    }

    if(!strcmp(tokens[0].c_str(), "g")) {
      if(current_vertex_count > 0) {
	Mesh mesh;
	mesh.name = last_name;
	mesh.start = last_end;
	mesh.end = vertex_count + last_end;
	mesh.material = mtl_loader.materials[last_material];

	mesh_list.push_back(mesh); 
	ret.push_back(mesh); 
      }

      last_name = tokens[1];
      last_end = vertex_count;
    } else if(!strcmp(tokens[0].c_str(), "f")) {
      if(tokens.size() == 4) {
	vertex_count += 3;
	current_vertex_count += 3;
      } else if(tokens.size() == 5) {
	vertex_count += 6;
	current_vertex_count += 6;
      }
    } else if(!strcmp(tokens[0].c_str(), "mtllib")) {
      mtl_loader.load_materials("assets/" + tokens[1]);
    } else if(!strcmp(tokens[0].c_str(), "usemtl")) {
      last_material = tokens[1];
    }
  }
  Mesh mesh;
  mesh.name = last_name;
  mesh.start = last_end;
  mesh.end = vertex_count + last_end;
  mesh.material = mtl_loader.materials[last_material];

  mesh_list.push_back(mesh); 
  ret.push_back(mesh);

  file.close();
  last_end = vertex_count;

  return ret;
}

void ObjLoader::load_preloaded_data() {
  std::cout << "Reserving " << vertex_count << " for vertex array" << std::endl;
  vertex_array->reserve(vertex_count);
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
