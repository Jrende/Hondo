#ifndef __HONDO_RENDERER_H__
#define __HONDO_RENDERER_H__
class Renderer;
#include <string>
#include "RenderObject.h"
#include <stdlib.h>
class Renderer {
  private:
    std::vector<std::shared_ptr<RenderObject> > renderList;
    SimpleShader shader;
  public:
    Renderer();
    void addObject(std::shared_ptr<RenderObject> rObj);
    void render();
};
#endif
