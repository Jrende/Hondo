#version 440
out vec4 outColor;

uniform vec3 from;
uniform vec3 to;
uniform vec3 color;
uniform mat4 mvp_mat;

void main() {
      outColor = vec4(color, 0.1f);
}
