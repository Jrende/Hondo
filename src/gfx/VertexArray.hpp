#ifndef __HONDO_VERTEXARRAY_H__
#define __HONDO_VERTEXARRAY_H__
class VertexArray;
#include <GL/glew.h>
#include <vector>
#include <memory>

#include "Mesh.hpp"
class VertexArray {
  private:
    unsigned int vertex_count;
    std::vector<unsigned int> attribute_sizes;
    std::shared_ptr<std::vector<float>> vertex_data;
    std::shared_ptr<std::vector<unsigned int>> index_data;

    unsigned int attr_size_sum;
    GLuint vao_id, vbo_id, index_buf_id;
    void flip(void);
    void init();
  public:
    bool is_bound;
    VertexArray();
    VertexArray(
	std::shared_ptr<std::vector<float>> vertex_data,
	std::shared_ptr<std::vector<unsigned int>> index_data,
	unsigned int size,
	std::vector<unsigned int> attribute_sizes);
    VertexArray(const VertexArray& other);
    ~VertexArray();
    void render(Mesh mesh);
    void render_array(GLuint mode);
    void bind();
    void unbind();
};
#endif
