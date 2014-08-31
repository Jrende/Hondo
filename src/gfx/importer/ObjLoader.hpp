#ifndef __HONDO_OBJLOADER_H__
#define __HONDO_OBJLOADER_H__
class ObjLoader;
#include <string>
#include <vector>
#include <array>
#include <set>
#include <memory>
#include "MtlLoader.hpp"
#include "../Mesh.hpp"

struct Vertex {
  std::array<float, 3> pos;
  std::array<float, 2> uv;
  std::array<float, 3> normal;
};

struct Face {
  std::vector<Vert> verts;
};

class ObjLoader {
  private:
    std::vector<std::array<float, 3>> posList;
    std::vector<std::array<float, 2>> uvList;
    std::vector<std::array<float, 3>> normalList;
    std::map<std::string, unsigned int> loaded_vertices_map;
    
    void createFace(const std::vector<std::string>& face);
    std::vector<std::string> file_list;
    unsigned int last_index_count;
    unsigned int last_index;
    unsigned int last_end;
    std::string last_name;
    std::string last_material;
    MtlLoader mtl_loader;
  public:

    ObjLoader();

    std::vector<Mesh> mesh_list;
    unsigned int vertex_count;

    std::shared_ptr<std::vector<float>> vertex_array;
    std::shared_ptr<std::vector<unsigned int>> index_array;

    void load_preloaded_data();
    void load_file(const std::string& path);
    void handleTokens(std::vector<std::string>& tokens);
    std::vector<Mesh> preload(const std::string& filename);
};
#endif
