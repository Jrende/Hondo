#version 330
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 TexCoord;
layout (location = 2) in vec3 Normal;
layout (location = 3) in vec3 Tangent;

uniform mat4 mvp_mat;

out vec3 TexCoord0;

void main() {
  gl_Position = mvp_mat * vec4(Position, 1.0);
  TexCoord0 = TexCoord;
}
