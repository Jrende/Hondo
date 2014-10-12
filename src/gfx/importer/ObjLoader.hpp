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
    const int MODEL_LIMIT = 1000;
    void create_face(const std::vector<std::string>& face);
    void create_vertex_arrays();

    std::map<std::string, int> loaded_vertices;
    std::map<std::shared_ptr<Mesh>, std::vector<float>> vertices_per_mesh;
    std::map<std::shared_ptr<Mesh>, std::vector<int>> indices_per_mesh;
    std::vector<std::shared_ptr<Mesh>> meshes;
    MtlLoader mtl_loader;
  public:
    ObjLoader();

    std::vector<Mesh> load_meshes(const std::string& path);
    void create_vertex_arrays(const std::string& filename);
    void handleTokens(std::vector<std::string>& tokens);
};
#endif
