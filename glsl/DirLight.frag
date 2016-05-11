#version 330
in vec3 TexCoord0;
in vec3 Normal0;
in vec3 WorldPos0;
in vec3 Tangent0;
in vec3 Bitangent0;

out vec4 FragColor;

uniform struct DirectionalLight {
    vec3 color;
    vec3 direction;
    float ambientIntensity;
    float diffuseIntensity;
} dirLight;

uniform sampler2D diffuse_sampler;
uniform sampler2D normal_sampler;
uniform sampler2D specular_sampler;
uniform sampler2D mask_sampler;

uniform float specular_intensity;
uniform float specular_exponent;

uniform vec3 eyePos;
uniform vec3 eyeDir;

vec3 getNormal() {
  vec3 normal = normalize(Normal0);
  vec3 tangent = normalize(Tangent0);
  vec3 bitangent = normalize(Bitangent0);
  vec3 bumpmapNormal = 2.0 * texture2D(normal_sampler, TexCoord0.st).xyz - vec3(1, 1, 1);
  return normalize(mat3(tangent, bitangent, normal) * bumpmapNormal);
}

vec3 getDiffuse(vec3 normal) {
  vec3 surfaceToLight = normalize(-dirLight.direction);

  float brightness = clamp(dot(normal, normalize(surfaceToLight)), 0, 1);

  vec3 diffuseColor = dirLight.color * dirLight.diffuseIntensity;
  return diffuseColor * brightness;
}

vec3 getSpecular(vec3 normal) {
  float diffuseFactor = dot(normal, dirLight.direction);
  vec3 diffuseColor = dirLight.color *
    dirLight.diffuseIntensity *
    diffuseFactor;

  vec3 VertexToEye = normalize(eyePos - WorldPos0);
  vec3 LightReflect = normalize(reflect(dirLight.direction, normal));
  float SpecularFactor = dot(VertexToEye, LightReflect);
  float specularIntensity = texture2D(specular_sampler, TexCoord0.st).x * specular_intensity;
  SpecularFactor = clamp(pow(SpecularFactor, specular_exponent), 0, 1);
  return dirLight.color *  SpecularFactor * specularIntensity;
}

void main() {
  if(texture2D(mask_sampler, TexCoord0.st).x < 0.5f) {
    discard;
  }
  vec3 normal = getNormal();
  vec4 color = texture2D(diffuse_sampler, TexCoord0.st);
  vec3 specularColor = getSpecular(normal);
  vec3 diffuseColor = getDiffuse(normal);
  vec3 ambientColor = dirLight.color * dirLight.ambientIntensity;
  FragColor = color * vec4(ambientColor + diffuseColor + specularColor, 1.0);
}
