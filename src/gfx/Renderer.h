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
    std::vector<RenderObject> renderList;
    std::shared_ptr<Camera> camera;
	Renderer(const Renderer& other);
  public:
    Renderer(int width, int height);
    void add_object(const RenderObject& rObj);
    void set_camera(std::shared_ptr<Camera> camera);
    void render();
};
#endif
