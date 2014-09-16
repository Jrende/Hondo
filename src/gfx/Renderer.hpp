#ifndef HONDO_RENDERER_HPP
#define HONDO_RENDERER_HPP
class Renderer;
#include <map>
#include <memory>
#include <glm/glm.hpp>

#include "Camera.hpp"
#include "DebugRenderer.hpp"
#include "RenderObject.hpp"
#include "VertexArray.hpp"
#include "lights/PointLight.hpp"
#include "lights/Light.hpp"
#include "lights/SpotLight.hpp"
#include "shader/LightShader.hpp"
#include "shader/SpotLightShader.hpp"
#include "shader/PointLightShader.hpp"
class Renderer {
  private:
    glm::mat4 perspective_mat;
    DebugRenderer debug_renderer;
    Camera camera;
    std::shared_ptr<PointLightShader> point_light_shader;
    std::shared_ptr<SpotLightShader> spot_light_shader;
    std::shared_ptr<LightShader> dir_light_shader;

    std::map<VertexArray, std::vector<std::shared_ptr<RenderObject>>> render_map;
    std::map<std::shared_ptr<LightShader>, std::vector<std::shared_ptr<Light>>> lights;
    Renderer(const Renderer& other) = delete;
  public:
    Renderer(int width, int height);
    Camera& get_camera();
    void add_object(std::shared_ptr<RenderObject> rObj);

    void add_light(std::shared_ptr<PointLight> point_light);
    void add_light(std::shared_ptr<SpotLight> spot_light);
    void add_light(std::shared_ptr<Light> light);

    void toggle_wireframe();
    void render();
    void draw_line(const glm::vec3& from, const glm::vec3& to, const glm::vec3& color);
    void draw_point(const glm::vec3& pos);
};
#endif
