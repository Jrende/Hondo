#ifndef HONDO_OBJLOADER_HPP
#define HONDO_OBJLOADER_HPP
class ObjLoader;
#include <string>
#include <vector>
#include <array>
#include <set>
#include <memory>
#include "MtlLoader.hpp"
#include "../Mesh.hpp"

class ObjLoader {
  private:
    void createFace(const std::vector<std::string>& face);

    std::vector<std::array<float, 3>> posList;
    std::vector<std::array<float, 2>> uvList;
    std::vector<std::array<float, 3>> normalList;
    std::map<std::string, unsigned int> loaded_vertices_map;
    
    MtlLoader mtl_loader;
    std::vector<std::string> file_list;
    unsigned int last_index_count = 0;
    unsigned int last_index = 0;
    unsigned int last_end = 0;
    std::string last_name = "";
    std::string last_material = "";
  public:
    unsigned int vertex_count = 0;

    ObjLoader();

    std::vector<Mesh> mesh_list;

    std::vector<float> vertex_array;
    std::vector<unsigned int> index_array;

    void load_preloaded_data();
    void load_file(const std::string& path);
    void handleTokens(std::vector<std::string>& tokens);
    void preload(const std::string& filename);
};
#endif
