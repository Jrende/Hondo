#ifndef __HONDO_RENDERER_H__
#define __HONDO_RENDERER_H__
class Renderer;
#include <map>
#include <memory>
#include <glm/glm.hpp>

#include "Camera.hpp"
#include "DebugRenderer.hpp"
#include "RenderObject.hpp"
#include "VertexArray.hpp"
#include "lights/PointLight.hpp"
#include "shader/LightShader.hpp"
#include "shader/PointLightShader.hpp"
#include "shader/SimpleShader.hpp"
class Renderer {
  private:
    glm::mat4 perspective_mat;

    //SimpleShader shader;
    DebugRenderer debug_renderer;
    std::shared_ptr<PointLightShader> point_light_shader;

    std::map<std::shared_ptr<VertexArray>, std::vector<std::shared_ptr<RenderObject>>> render_map;
    std::map<std::shared_ptr<LightShader>, std::vector<std::shared_ptr<Light>>> lights;
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
    void add_light(const std::shared_ptr<Light>& point_light);
};
#endif
