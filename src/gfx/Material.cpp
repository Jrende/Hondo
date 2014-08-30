#include "Material.hpp"
Material::Material() {

}
Material::Material(std::string name):
  name(name),
  specular_intensity(5.0f),
  specular_exponent(100.0f)
{
}
