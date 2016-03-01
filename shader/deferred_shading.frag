#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D gPositionDepth;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;
uniform sampler2D ssao;

void main(){

	vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
	float SSAO = texture(ssao, TexCoords).r;

	FragColor = vec4( Diffuse * SSAO, 1.0f);
	return;
}
