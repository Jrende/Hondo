#pragma once
class Renderer;
#include <map>
#include <memory>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <unordered_map>

#include "Camera.hpp"
#include "DebugRenderer.hpp"
#include "DepthBuffer.hpp"
#include "RenderObject.hpp"
#include "SkyBox.hpp"
#include "VertexArray.hpp"
#include "lights/Light.hpp"
#include "lights/PointLight.hpp"
#include "lights/SpotLight.hpp"
#include "lights/DirLight.hpp"
#include "shader/DepthShader.hpp"
#include "shader/LightShader.hpp"
#include "shader/PointLightShader.hpp"
#include "shader/SkyShader.hpp"
#include "shader/SpotLightShader.hpp"
#include "ecs/World.hpp"

class Renderer {
  private:
    int width, height;
    glm::mat4 perspective_mat;
    DebugRenderer debug_renderer;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<PointLightShader> point_light_shader;
    std::shared_ptr<SpotLightShader> spot_light_shader;
    std::shared_ptr<LightShader> dir_light_shader;
    glm::mat4 ortho;
    glm::mat4 depth_bias_mat;
    std::vector<std::shared_ptr<Light>> light_list;
    DepthShader depth_shader;
    int shown_light_index = -1;
    int last_shown_light_index = 0;
    SkyShader sky_shader;
    std::unique_ptr<RenderObject> skybox;
    std::map<std::shared_ptr<LightShader>, std::vector<std::shared_ptr<Light>>> lights;
    Renderer(const Renderer& other) = delete;
    void draw_sky();
    void render_depth_test(std::vector<RenderObject>& render_list);
    void render_scene(const glm::mat4& vp_mat, std::vector<RenderObject>& render_list);
  public:
    Renderer(int width, int height);
    void set_camera(std::shared_ptr<Camera> camera);

    void add_light(std::shared_ptr<PointLight> point_light);
    void add_light(std::shared_ptr<SpotLight> spot_light);
    void add_light(std::shared_ptr<DirLight> light);

    void set_skybox(RenderObject&& skybox);

    void toggle_wireframe();
    void toggle_shadow_map();
    void pre_render();

    void render(std::vector<RenderObject>& render_list);
    void render(World& world);

    void show_single_light(int index);
    std::shared_ptr<Light> get_shown_light();
    int light_count();
    void draw_lines(const std::vector<std::pair<glm::vec3, glm::vec3>>& lines, const glm::vec3& color);
    void draw_line(const glm::vec3& from, const glm::vec3& to, const glm::vec3& color);
    void draw_point(const glm::vec3& pos);
    void clear_lights();
};
