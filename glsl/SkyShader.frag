#version 330
in vec3 Position0;
in vec3 TexCoord0;
in vec3 Normal0;
in vec3 Tangent0;
in vec3 Bitangent0;

out vec4 FragColor;

void main() {
	vec3 up = vec3(0, 1.0f, 0);
	float gradient = dot(Normal0, -up) + 0.2;
	vec3 color = mix(vec3(0.0,0.0,0.0), vec3(0.2,0.2,0.8), gradient);
	FragColor = vec4(color, 1.0f);
}
