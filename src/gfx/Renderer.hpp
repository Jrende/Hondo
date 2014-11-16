#ifndef HONDO_RENDERER_HPP
#define HONDO_RENDERER_HPP
class Renderer;
#include <map>
#include <memory>
#include <glm/glm.hpp>
#include <GL/glew.h>

#include "Camera.hpp"
#include "DebugRenderer.hpp"
#include "RenderObject.hpp"
#include "SkyBox.hpp"
#include "VertexArray.hpp"
#include "lights/Light.hpp"
#include "lights/PointLight.hpp"
#include "lights/SpotLight.hpp"
#include "shader/LightShader.hpp"
#include "shader/PointLightShader.hpp"
#include "shader/SkyShader.hpp"
#include "shader/SpotLightShader.hpp"

class Renderer {
  private:
    glm::mat4 perspective_mat;
    DebugRenderer debug_renderer;
    Camera camera;
    std::shared_ptr<PointLightShader> point_light_shader;
    std::shared_ptr<SpotLightShader> spot_light_shader;
    std::shared_ptr<LightShader> dir_light_shader;
    std::vector<std::shared_ptr<Light>> light_list;
    int shown_light_index = -1;
    int last_shown_light_index = 0;
    SkyShader sky_shader;
    std::shared_ptr<SkyBox> skybox;

    std::map<VertexArray, std::vector<std::shared_ptr<RenderObject>>> render_map;
    std::map<std::shared_ptr<LightShader>, std::vector<std::shared_ptr<Light>>> lights;
    Renderer(const Renderer& other) = delete;
    void draw_sky();
  public:
    Renderer(int width, int height);
    Camera& get_camera();

    void add_object(std::shared_ptr<RenderObject> rObj);
    void add_light(std::shared_ptr<PointLight> point_light);
    void add_light(std::shared_ptr<SpotLight> spot_light);
    void add_light(std::shared_ptr<Light> light);

    void set_skybox(std::shared_ptr<SkyBox> skybox);

    void toggle_wireframe();
    void pre_render();
    void render();
    void show_single_light(int index);
    std::shared_ptr<Light> get_shown_light();
    int light_count();
    void draw_lines(const std::vector<std::pair<glm::vec3, glm::vec3>>& lines, const glm::vec3& color);
    void draw_line(const glm::vec3& from, const glm::vec3& to, const glm::vec3& color);
    void draw_point(const glm::vec3& pos);
};
#endif
