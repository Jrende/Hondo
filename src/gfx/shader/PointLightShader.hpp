#ifndef HONDO_POINTLIGHTSHADER_HPP
#define HONDO_POINTLIGHTSHADER_HPP
class PointLightShader;
#include <glm/glm.hpp>

#include "../lights/Light.hpp"
#include "../lights/PointLight.hpp"
#include "LightShader.hpp"
#include "ShaderProgram.hpp"
class PointLightShader: public LightShader {
  private:
    int debug;
    GLuint light_constant_id,
	   light_exp_id,
	   light_linear_id;
    void set_light_constant(float light_constant);
    void set_light_exp(float light_exp);
    void set_light_linear(float light_linear);
  public:
    PointLightShader(); 
    void set_light(const Light& light);
};
#endif
