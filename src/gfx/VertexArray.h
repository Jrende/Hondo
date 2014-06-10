#ifndef __HONDO_VERTEXARRAY_H__
#define __HONDO_VERTEXARRAY_H__
class VertexArray;
#include<vector>
#include <GL/glew.h>
class VertexArray {
  private:
    std::vector<float> vertex_data;
    const int pos_len = 3;
    int vertex_len = 0;
    GLuint vao_id, vbo_id, index_buf_id;
  public:
    VertexArray();
    VertexArray(const VertexArray& other);
    VertexArray(std::vector<std::vector<float>> vertices);
    ~VertexArray();
    int size(void);
    void add_vertex(float x, float y, float z);
    void add_vertices(const std::vector<std::vector<float>> &vertices);
    void flip(void);
    void render(void);
};
#endif
