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
#include "../VertexArray.hpp"
#include "ObjLoaderUtils.hpp"

class ObjLoader {
  private:
    MtlLoader mtl_loader;
    std::map<std::string, std::vector<Mesh>> meshes_per_file;
    std::vector<std::shared_ptr<VertexArray>> vertex_array_store;

    std::vector<std::vector<float>> vertex_data_store;
    std::vector<std::vector<unsigned int>> index_data_store;
    std::vector<std::vector<unsigned int>> attr_data_store;

    std::vector<float> vertex_buffer;
    std::vector<unsigned int> index_buffer;
    std::vector<std::string> paths;
    unsigned int vertices_count = 0;
    unsigned int indices_count = 0;
    unsigned int last_index = 0;
    Mesh current_mesh;

    std::map<std::string, int> loaded_vertices;
    std::vector<float> pos;
    std::vector<float> uvs;
    std::vector<float> normals;

    void create_face(std::vector<std::string> tokens);
    void add_face(Face& face);
    void add_vertex_to_indices(int index);
    void create_vertex(const std::string& vertex_string, Vertex& vertex);
  public:
    void load_files();
    void preload_file(const std::string& path);
    const std::vector<Mesh>& get_meshes(const std::string& path);
};
#endif
