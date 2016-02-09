#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 textureCoords;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;

uniform mat4 Model;
uniform mat4 ViewProjection;

uniform vec2 TexRatio;
uniform vec2 TexShift;

void main(){
	vec4 worldPos = Model * vec4(position, 1.0f);
	FragPos = worldPos.xyz;
	gl_Position = ViewProjection * worldPos;

	mat3 normalMatrix = transpose(inverse(mat3(Model)));
	Normal = normalMatrix * normal;

	TexCoords = vec2(textureCoords.x, 1-textureCoords.y);

	// Handle animated texture if needed
	if(TexRatio.x != -1){
		TexCoords = (TexCoords*TexRatio) + TexShift;
	}
}
