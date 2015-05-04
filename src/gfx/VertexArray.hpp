#ifndef HONDO_VERTEXARRAY_HPP
#define HONDO_VERTEXARRAY_HPP
class VertexArray;
#include <GL/glew.h>
#include <vector>
#include <memory>

#include "Mesh.hpp"
class VertexArray {
  private:
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
	const std::vector<float>& vertex_data,
	const std::vector<unsigned int>& index_data,
	std::vector<unsigned int> attribute_sizes);
    ~VertexArray();
    void render(const Mesh& mesh) const;
    void render_elements(GLuint mode, unsigned int size);
    void bind() const;
    void unbind() const;
    void swap(VertexArray& l, VertexArray& r);
    VertexArray& operator=(VertexArray& other) = default;
    VertexArray& operator=(VertexArray&& other);
};
#endif
