#version 330
layout(location = 0) in vec3 position;
out vec3 pos;
uniform mat4 mvpMat;

void main() {
      gl_Position = mvpMat * vec4(position, 1.0);
}
