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
    MtlLoader mtl_loader;
  public:
    ObjLoader();

    std::vector<std::shared_ptr<Mesh>> load_meshes(const std::string& path);
    void create_vertex_arrays(const std::string& filename);
    void handleTokens(std::vector<std::string>& tokens);
};
#endif
