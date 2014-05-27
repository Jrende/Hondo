#ifndef __HONDO_TRIANGLE_H__
#define __HONDO_TRIANGLE_H__
class Triangle;
#include "VertexArray.h"
class Triangle {
  private:
    VertexArray vArray;
  public:
    Triangle();
    ~Triangle();
    void render();
};
#endif
