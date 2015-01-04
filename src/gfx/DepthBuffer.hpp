#pragma once
class DepthBuffer;
#include <GL/glew.h>
class DepthBuffer {
  private:
  public:
    GLuint depth_tex, fb;
    unsigned int width, height;
    DepthBuffer();
    ~DepthBuffer();
    void bind();
    void unbind();
    void bind_shadowmap(GLuint unit);
};
