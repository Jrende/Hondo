#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;
layout(location = 2) in vec3 normal;

uniform mat4 mvp_mat;

void main() {
  gl_Position = mvp_mat * vec4(position, 1.0);
}
