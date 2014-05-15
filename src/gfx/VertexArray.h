#ifndef __HONDO_VERTEXARRAY_H__
#define __HONDO_VERTEXARRAY_H__
class VertexArray;
#include<vector>
#include <GL/glew.h>
class VertexArray {
  private:
    std::vector<float> vertex_data;
    const int pos_len = 3;

    GLuint vao_id;
    GLuint vbo_id;
    GLuint index_buf_id;
  public:
    VertexArray();
    ~VertexArray();
    int size();
    void add_vertex(float, float, float);
    void print();
    void flip();
    void render();
};
#endif
