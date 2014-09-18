#ifndef HONDO_SPOTLIGHTSHADER_HPP
#define HONDO_SPOTLIGHTSHADER_HPP
class SpotLightShader;
#include <glm/glm.hpp>

#include "../lights/Light.hpp"
#include "../lights/SpotLight.hpp"
#include "LightShader.hpp"
#include "ShaderProgram.hpp"
class SpotLightShader: public LightShader {
  private:
    int debug;
    GLuint light_constant_id,
	   light_exp_id,
	   light_linear_id,
	   light_concentration_id,
	   light_direction_id;
    void set_light_concentration(float light_concentration);
    void set_light_direction(const glm::vec3& light_direction);
    void set_light_constant(float light_constant);
    void set_light_linear(float light_linear);
    void set_light_exp(float light_exp);

  public:
    SpotLightShader(); 
    void set_light(const Light& light);
};
#endif
