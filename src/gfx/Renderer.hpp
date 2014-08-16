#ifndef __HONDO_RENDERER_H__
#define __HONDO_RENDERER_H__
class Renderer;
#include <map>
#include <memory>
#include <glm/glm.hpp>

#include "DebugRenderer.hpp"
#include "RenderObject.hpp"
#include "shader/SimpleShader.hpp"
#include "Camera.hpp"
#include "VertexArray.hpp"
class Renderer {
  private:
    glm::mat4 perspective_mat;

    SimpleShader shader;
    DebugRenderer debug_renderer;

    std::map<std::shared_ptr<VertexArray>, std::vector<std::shared_ptr<RenderObject>>> render_map;
    std::shared_ptr<Camera> camera;
    Renderer(const Renderer& other);
  public:
    Renderer(int width, int height);
    void add_object(const std::shared_ptr<RenderObject>& rObj);
    void set_camera(std::shared_ptr<Camera> camera);
    void render();
    void toggle_wireframe();
    void draw_line(const glm::vec3& from, const glm::vec3& to);
    void draw_point(const glm::vec3& pos);
};
#endif
