#ifndef HONDO_LIGHTSHADER_HPP
#define HONDO_LIGHTSHADER_HPP
class LightShader;
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <string>

#include "../Material.hpp"
#include "../lights/Light.hpp"
#include "ShaderProgram.hpp"
class LightShader {
  protected:
    ShaderProgram shader_program;
  private:
    std::string light_name;
    GLuint mvp_mat_id,
	   depth_mvp_mat_id,
	   model_mat_id,
	   eye_pos_id,
	   eye_dir_id,
	   diffuse_sampler_id,
	   specular_sampler_id,
	   normal_sampler_id,
	   shadow_sampler_id,
	   light_color_id,
	   light_ambientintensity_id,
	   light_position_id,
	   light_direction_id,
	   light_diffuseintensity_id,
	   diffuse_id,
	   ambient_id,
	   specular_id,
	   specular_intensity_id,
	   specular_exponent_id;
  public:
    LightShader(); 
    LightShader(std::string name, std::string light_name);
    void use_shader();
    void stop();
    void set_diffuse_sampler(int sampler);
    void set_specular_sampler(int sampler);
    void set_normal_sampler(int sampler);
    void set_shadow_sampler(int sampler);

    void set_mvp_mat(const glm::mat4& mvp_mat);
    void set_depth_mvp_mat(const glm::mat4& depth_mvp_mat);
    void set_model_mat(const glm::mat4& mvp_mat);
    void set_eye_pos(const glm::vec3& eye_pos);
    void set_eye_dir(const glm::vec3& eye_dir);
    void set_light_color(const glm::vec3& light_color);
    void set_light_ambientintensity(float light_ambientintensity);
    void set_light_diffuseintensity(float light_diffuseintensity);
    void set_light_position(const glm::vec3& light_position);
    void set_light_direction(const glm::vec3& light_direction);
    void set_material(const Material& mat);
    bool operator<(const LightShader& other) const;
    virtual void set_light(const Light& light);
};
#endif
