#version 330
out vec4 FragColor;
uniform sampler2D sampler;

in vec3 position0;
in vec2 tex_coord0;


void main() {
  float depth = texture2D(sampler, tex_coord0).x;
  FragColor = vec4(vec3(depth), 1.0f);
}
