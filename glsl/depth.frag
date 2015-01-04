#version 440
out vec4 FragColor;

uniform mat4 mvp_mat;

void main() {
  FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
}
