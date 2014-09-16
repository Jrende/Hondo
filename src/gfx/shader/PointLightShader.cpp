#include "PointLightShader.hpp"
#include "ShaderProgram.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
PointLightShader::PointLightShader(): 
  LightShader("PointLight", "pointLight"),
  light_constant_id(shader_program.get_uniform("pointLight.constant")),
  light_exp_id(shader_program.get_uniform("pointLight.exp")),
  light_linear_id(shader_program.get_uniform("pointLight.linear"))
{
}

void PointLightShader::set_light_constant(float light_constant) {
  glUniform1f(light_constant_id, light_constant);
}

void PointLightShader::set_light_exp(float light_exp) {
  glUniform1f(light_exp_id, light_exp);
}

void PointLightShader::set_light_linear(float light_linear) {
  glUniform1f(light_linear_id, light_linear);
}

void PointLightShader::set_light(const Light& light) {
  LightShader::set_light(light);
  const auto& pl = static_cast<const PointLight&>(light);
  set_light_constant(pl.constant);
  set_light_exp(pl.exponential);
  set_light_linear(pl.linear);
}
