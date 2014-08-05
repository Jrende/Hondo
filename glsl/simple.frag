#version 440
in vec3 pos;
out vec4 outColor;

uniform struct Instance {
  mat4 mvpMat;
  vec3 color;
} instance;
/*
layout(std430, binding=2) buffer MyBuffer {
  Instance instance[];
}
*/
void main() {
      outColor =  vec4(instance.color, 1.0);
}
