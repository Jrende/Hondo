#version 440
out vec4 FragColor;

uniform mat4 mvp_mat;
uniform sampler2D mask_sampler;
in vec3 TexCoord0;

void main() {
  if(texture2D(mask_sampler, TexCoord0.st).x < 0.5f) {
    discard;
  }
  FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
}
