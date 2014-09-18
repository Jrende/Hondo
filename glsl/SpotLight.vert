#version 330
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 TexCoord;
layout (location = 2) in vec3 Normal;
layout (location = 3) in vec3 Tangent;
layout (location = 4) in vec3 Bitangent;

out vec3 TexCoord0;
out vec3 Normal0;
out vec3 WorldPos0;
out vec3 Tangent0;
out vec3 Bitangent0;

uniform mat4 mvpMatrix;
uniform mat4 modelMatrix;

uniform vec3 eyePos;
uniform vec3 eyeDir;

void main(void) {
	gl_Position = mvpMatrix * vec4(Position, 1.0);
	TexCoord0 = TexCoord;
	Normal0 = (modelMatrix * vec4(Normal, 0.0)).xyz;
	WorldPos0 = (modelMatrix * vec4(Position, 1)).xyz;
	Tangent0 = (modelMatrix * vec4(Tangent, 0.0)).xyz;
	Bitangent0 = (modelMatrix * vec4(Bitangent, 0.0)).xyz;
}
