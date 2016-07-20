#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 textureCoords;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;
out float Alpha;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform vec2 TexRatio;
uniform vec2 TexShift;

uniform float in_alpha;

void main(){
	mat4 ModelView = View * Model;
	vec4 viewPos = ModelView * vec4(position, 1.0f);
	FragPos = viewPos.xyz;
	gl_Position = Projection * viewPos;

	mat3 normalMatrix = transpose(inverse(mat3(ModelView)));
	Normal = normalMatrix * normal;

	TexCoords = vec2(textureCoords.x, 1-textureCoords.y);

	Alpha = in_alpha;

	// Handle animated texture if needed
	if(TexRatio.x != -1){
		TexCoords = (TexCoords*TexRatio) + TexShift;
	}
}
