#version 330
layout(points) in;
layout(line_strip, max_vertices = 2) out;

uniform vec3 from;
uniform vec3 to;
uniform vec3 color;
uniform mat4 mvp_mat;

void main() {
  gl_Position = gl_in[0].gl_Position;
  EmitVertex();

  gl_Position = gl_in[0].gl_Position + mvp_mat * vec4(to, 1.0);
  EmitVertex();

  EndPrimitive();
}
