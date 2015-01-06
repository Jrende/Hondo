#version 330
in vec3 TexCoord0;
in vec3 Normal0;
in vec3 WorldPos0;
in vec3 Tangent0;
in vec3 Bitangent0;
in vec3 ShadowCoord0;

out vec4 FragColor;

uniform struct SpotLight {
  vec3 color;
  vec3 position;
  vec3 direction;
  float ambientIntensity;
  float diffuseIntensity;
  float concentration;
  float constant;
  float linear;
  float exp;
} spotLight;


uniform sampler2D diffuse_sampler;
uniform sampler2D normal_sampler;
uniform sampler2D specular_sampler;
uniform sampler2D shadow_sampler;

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

vec4 getDiffuse(vec3 normal, vec3 surfaceToLight, float shadow) {
  float distance = length(surfaceToLight);
  float brightness = pow(clamp(dot(-spotLight.direction, normalize(surfaceToLight)), 0, 1), spotLight.concentration) * spotLight.color;
  brightness *= max(dot(normal, normalize(surfaceToLight)), 0);
  brightness /= spotLight.constant + spotLight.linear*distance + spotLight.exp*distance*distance;

  vec4 lightColor =  vec4(spotLight.color, 1.0f);
  vec4 diffuseColor = lightColor * spotLight.diffuseIntensity * shadow;
  vec4 ambientColor = lightColor * spotLight.ambientIntensity * shadow;
  return diffuseColor * brightness + ambientColor;
}


vec4 getSpecular(vec3 normal, vec3 surfaceToLight, float shadow) {
  vec3 lightReflect = normalize(reflect(-surfaceToLight, normal));
  vec3 surfaceToEye = normalize(eyePos - WorldPos0);

  float specularFactor = clamp(dot(surfaceToEye, lightReflect), 0.0, 1.0);
  float specularIntensity = texture2D(specular_sampler, TexCoord0.st).x * specular_intensity;
  specularFactor = pow(specularFactor, specular_exponent);
  return vec4(spotLight.color, 1.0f) * specularIntensity * specularFactor * shadow;
}

vec2 poissonDisk[4] = vec2[](
  vec2( -0.94201624, -0.39906216 ),
  vec2( 0.94558609, -0.76890725 ),
  vec2( -0.094184101, -0.92938870 ),
  vec2( 0.34495938, 0.29387760 )
);
float getShadow(vec3 normal, vec3 surfaceToLight) {
  float cosTheta = clamp(dot(normal, surfaceToLight), 0, 1);
  float visibility = 1.0;

  float bias = clamp(tan(acos(cosTheta)), 0.0, 0.01);
  for (int i=0;i<4;i++){
    float shadow_distance = texture2D(shadow_sampler, ShadowCoord0.xy + poissonDisk[i]/700.0).x;
    if(shadow_distance < ShadowCoord0.z - bias) {
      visibility-=0.2;
    }
  }
  return visibility;
}

void main() {
  vec3 surfaceToLight = spotLight.position - WorldPos0;
  vec3 normal = getNormal();
  vec4 color = texture2D(diffuse_sampler, TexCoord0.st);
  float shadow = getShadow(normal, surfaceToLight);
  color += getSpecular(normal, surfaceToLight, shadow);
  color *= getDiffuse(normal, surfaceToLight, shadow);
  FragColor = color;
}
