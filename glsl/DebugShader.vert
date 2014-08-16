#version 330
layout(location = 0) in vec3 position;

uniform mat4 mvp_mat;
uniform vec3 pos;
uniform vec3 color;

void main() {
  gl_Position = mvp_mat * vec4(pos, 1.0);
}

