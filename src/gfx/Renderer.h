#ifndef __HONDO_RENDERER_H__
#define __HONDO_RENDERER_H__
class Renderer;
#include <map>
#include <memory>
#include <glm/glm.hpp>

#include "RenderObject.h"
#include "shader/SimpleShader.h"
#include "Camera.h"
#include "VertexArray.h"
class Renderer {
  private:
    glm::mat4 perspective_mat;

    SimpleShader shader;
    std::vector<RenderObject> renderList;
    std::map<std::shared_ptr<VertexArray>, std::vector<RenderObject>> render_map;
    std::shared_ptr<Camera> camera;
    Renderer(const Renderer& other);
    int start, end;
  public:
    Renderer(int width, int height);
    void add_object(const RenderObject& rObj);
    void set_camera(std::shared_ptr<Camera> camera);
    void render();
    void toggle_wireframe();
    void add_start();
    void sub_start();
    void add_end();
    void sub_end();
};
#endif
