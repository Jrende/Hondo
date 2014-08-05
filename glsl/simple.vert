#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;
layout(location = 2) in vec3 normal;
out vec3 pos;

uniform struct Instance {
  mat4 mvpMat;
  vec3 color;
} instance;

void main() {
      gl_Position = instance.mvpMat * vec4(position, 1.0);
}
