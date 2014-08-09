#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;
layout(location = 2) in vec3 normal;

out vec3 pos0;
out vec2 tex_coord0;
out vec3 normal0;

uniform struct Instance {
  mat4 mvpMat;
  vec3 color;
  sampler2D diffuse_sampler;
} instance;

void main() {
      gl_Position = instance.mvpMat * vec4(position, 1.0);
      tex_coord0 = texcoord;
      normal0 = (instance.mvpMat * vec4(normal, 0.0)).xyz;
}
