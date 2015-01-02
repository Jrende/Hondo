#include "SpotLightShader.hpp"
#include "ShaderProgram.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
SpotLightShader::SpotLightShader(): 
  LightShader("SpotLight", "spotLight"),
  light_constant_id(shader_program.get_uniform("spotLight.constant")),
  light_exp_id(shader_program.get_uniform("spotLight.exp")),
  light_linear_id(shader_program.get_uniform("spotLight.linear")),
  light_concentration_id(shader_program.get_uniform("spotLight.concentration"))
{
}

void SpotLightShader::set_light_constant(float light_constant) {
  glUniform1f(light_constant_id, light_constant);
}

void SpotLightShader::set_light_exp(float light_exp) {
  glUniform1f(light_exp_id, light_exp);
}

void SpotLightShader::set_light_concentration(float light_concentration) {
  glUniform1f(light_concentration_id, light_concentration);
}

void SpotLightShader::set_light_linear(float light_linear) {
  glUniform1f(light_linear_id, light_linear);
}

void SpotLightShader::set_light(const Light& light) {
  LightShader::set_light(light);
  const auto& pl = static_cast<const SpotLight&>(light);
  set_light_constant(pl.constant);
  set_light_exp(pl.exponential);
  set_light_linear(pl.linear);
  set_light_concentration(pl.concentration);
}
