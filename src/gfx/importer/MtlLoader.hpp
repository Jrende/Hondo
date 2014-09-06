#ifndef HONDO_MTLLOADER_HPP
#define HONDO_MTLLOADER_HPP
class MtlLoader;
#include <map>
#include <vector>
#include <string>
#include <GL/glew.h>
#include "../Material.hpp"
#include "../Mesh.hpp"
class MtlLoader {
  private:
    std::string last_material_name;
    Material current_material;
    void handle_tokens(std::vector<std::string> tokens);
  public:
    std::map<std::string, Material> materials;
    void load_materials(const std::string& path);
    MtlLoader();
};
#endif
