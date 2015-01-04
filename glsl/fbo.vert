#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 tex_coord;
uniform sampler2D sampler;

out vec3 position0;
out vec2 tex_coord0;

void main() {
      gl_Position = vec4(position, 1.0) * 1024/768;
      tex_coord0 = tex_coord;
}

