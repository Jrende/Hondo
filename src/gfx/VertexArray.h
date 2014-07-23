#ifndef __HONDO_VERTEXARRAY_H__
#define __HONDO_VERTEXARRAY_H__
class VertexArray;
#include<vector>
#include <GL/glew.h>
class VertexArray {
  typedef unsigned int uint;
  private:
    uint vertex_count;
    std::vector<uint> attribute_sizes;
    //Should maybe be unique_ptr
    std::vector<float> vertex_data;

    uint attr_size_sum;
    GLuint vao_id, vbo_id, index_buf_id;
    void flip(void);
    void init();
  public:
    VertexArray();
    VertexArray(const std::vector<float>& vertex_data, uint size, std::vector<uint> attribute_sizes);
    VertexArray(const VertexArray& other);
    VertexArray(uint size, std::vector<uint> attribute_sizes);
    ~VertexArray();
    void render(void);
};
#endif
