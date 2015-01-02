#version 330
in vec3 TexCoord0;
in vec3 Normal0;
in vec3 WorldPos0;
in vec3 Tangent0;
in vec3 Bitangent0;

out vec4 FragColor;

uniform struct DirectionalLight {
    vec3 color;
    vec3 position;
    vec3 direction;
    float ambientIntensity;
    float diffuseIntensity;
} dirLight;

uniform sampler2D diffuse_sampler;
uniform sampler2D normal_sampler;
uniform sampler2D specular_sampler;

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

vec4 getDiffuse(vec3 normal) {
  vec3 surfaceToLight = normalize(-dirLight.direction);

  float brightness = clamp(dot(normal, normalize(surfaceToLight)), 0, 1);

  vec4 lightColor =  vec4(dirLight.color, 1.0f);
  vec4 diffuseColor = lightColor * dirLight.diffuseIntensity;
  vec4 ambientColor = lightColor * dirLight.ambientIntensity;
  return diffuseColor * brightness + ambientColor;
}

vec4 getSpecular(vec3 normal) {
  vec3 surfaceToLight = normalize(dirLight.direction) - WorldPos0;

  vec3 lightReflect = normalize(reflect(-surfaceToLight, normal));
  vec3 surfaceToEye = normalize(eyePos - WorldPos0);

  float specularFactor = clamp(dot(surfaceToEye, lightReflect), 0.0, 1.0);
  float specularIntensity = texture2D(specular_sampler, TexCoord0.st).x * specular_intensity;
  specularFactor = pow(specularFactor, specular_exponent);
  return vec4(dirLight.color, 1.0f) * specularIntensity * specularFactor;
}

void main() {
  vec3 normal = getNormal();
  vec4 color = texture2D(diffuse_sampler, TexCoord0.st);
  color += getSpecular(normal);
  color *= getDiffuse(normal);
  FragColor = color;
}
