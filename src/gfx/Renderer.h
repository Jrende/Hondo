#ifndef __HONDO_RENDERER_H__
#define __HONDO_RENDERER_H__
class Renderer;
#include "RenderObject.h"
#include "shader/SimpleShader.h"
#include "Camera.h"
#include <glm/glm.hpp>
class Renderer {
  private:
    glm::mat4 perspective_mat;

    SimpleShader shader;
    std::vector<std::shared_ptr<RenderObject> > renderList;
    std::shared_ptr<Camera> camera;
  public:
    Renderer(int width, int height);
    void addObject(std::shared_ptr<RenderObject> rObj);
    void setCamera(std::shared_ptr<Camera> camera);
    void render();
};
#endif
