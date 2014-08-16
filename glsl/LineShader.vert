#version 330
layout(location = 0) in vec3 position;

uniform vec3 from;
uniform vec3 to;
uniform vec3 color;
uniform mat4 mvp_mat;

void main() {
  gl_Position = mvp_mat * vec4(from, 1.0);
}

