#version 440
in vec3 pos0;
in vec2 tex_coord0;
in vec3 normal0;
out vec4 outColor;

uniform struct Instance {
  mat4 mvpMat;
  vec3 color;
  sampler2D diffuse_sampler;
} instance;

void main() {
      outColor =  vec4(texture2D(instance.diffuse_sampler, tex_coord0.st).xyz, 1.0);
}
