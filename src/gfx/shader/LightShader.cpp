#include "LightShader.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
LightShader::LightShader(std::string name): 
  shader_program(name),

  mvp_mat_id(shader_program.get_uniform("mvpMatrix")),
  model_mat_id(shader_program.get_uniform("modelMatrix")),
  eye_pos_id(shader_program.get_uniform("eyePos")),
  eye_dir_id(shader_program.get_uniform("eyeDir")),
  diffuse_sampler_id(shader_program.get_uniform("diffuse_sampler")),
  specular_sampler_id(shader_program.get_uniform("specular_sampler")),
  normal_sampler_id(shader_program.get_uniform("normal_sampler")),
  light_color_id(shader_program.get_uniform("pointLight.color")),
  light_ambientintensity_id(shader_program.get_uniform("pointLight.ambientIntensity")),
  light_position_id(shader_program.get_uniform("pointLight.position")),
  light_diffuseintensity_id(shader_program.get_uniform("pointLight.diffuseIntensity")),
  specular_intensity_id(shader_program.get_uniform("specular_intensity")),
  specular_exponent_id(shader_program.get_uniform("specular_exponent"))
{
}

void LightShader::use_shader() {
  shader_program.use();
}

void LightShader::stop() {
  shader_program.stop();
}

void LightShader::set_diffuse_sampler(int sampler) {
  glUniform1i(diffuse_sampler_id, sampler);
}

void LightShader::set_specular_sampler(int sampler) {
  glUniform1i(specular_sampler_id, sampler);
}

void LightShader::set_normal_sampler(int sampler) {
  glUniform1i(normal_sampler_id, sampler);
}

void LightShader::set_model_mat(const glm::mat4& model_mat) {
  glUniformMatrix4fv(model_mat_id, 1, GL_FALSE, glm::value_ptr(model_mat));
}

void LightShader::set_mvp_mat(const glm::mat4& mvp_mat) {
  glUniformMatrix4fv(mvp_mat_id, 1, GL_FALSE, glm::value_ptr(mvp_mat));
}

void LightShader::set_eye_pos(const glm::vec3& eye_pos) {
  glUniform3fv(eye_pos_id, 1, glm::value_ptr(eye_pos));
}

void LightShader::set_eye_dir(const glm::vec3& eye_dir) {
  glUniform3fv(eye_dir_id, 1, glm::value_ptr(eye_dir));
}

void LightShader::set_light_color(const glm::vec3& light_color) {
  glUniform3fv(light_color_id, 1, glm::value_ptr(light_color));
}

void LightShader::set_light_ambientintensity(float light_ambientintensity) {
  glUniform1f(light_ambientintensity_id, light_ambientintensity);
}

void LightShader::set_light_diffuseintensity(float light_diffuseintensity) {
  glUniform1f(light_diffuseintensity_id, light_diffuseintensity);
}

void LightShader::set_light_position(const glm::vec3& light_position) {
  glUniform3fv(light_position_id, 1, glm::value_ptr(light_position));
}

void LightShader::set_base_light(const Light& light) {
  set_light_position(light.pos);
  set_light_color(light.color);
  set_light_ambientintensity(light.ambient_intensity);
  set_light_diffuseintensity(light.diffuse_intensity);
}

void LightShader::set_material(const Material& mat) {
  glUniform1f(specular_intensity_id, mat.specular_intensity);
  glUniform1f(specular_exponent_id, mat.specular_exponent);
}

