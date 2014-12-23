#ifndef HONDO_VERTEXARRAY_HPP
#define HONDO_VERTEXARRAY_HPP
class VertexArray;
#include <GL/glew.h>
#include <vector>
#include <memory>

#include "Mesh.hpp"
class VertexArray {
  private:
    unsigned int vertex_count;
    unsigned int size;
    std::vector<unsigned int> attribute_sizes;
    std::vector<float> vertex_data;
    std::vector<unsigned int> index_data;
    void create_buffers();
    void init();
  public:
    VertexArray(const VertexArray& other);
    GLuint vao_id, vbo_id, index_buf_id;
    bool operator<(const VertexArray& other) const;
    VertexArray() = default;
    VertexArray(
	std::vector<float> vertex_data,
	std::vector<unsigned int> index_data,
	unsigned int size,
	std::vector<unsigned int> attribute_sizes);
    ~VertexArray();
    void render(const Mesh& mesh) const;
    void render_array(GLuint mode);
    void bind() const;
    void unbind() const;
    void swap(VertexArray& l, VertexArray& r);
    VertexArray& operator=(VertexArray& other) = default;
    VertexArray& operator=(VertexArray&& other);
};
#endif
