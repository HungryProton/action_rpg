#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D gPositionDepth;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;
uniform sampler2D ssao;

float GetVignetteFactor(){
	vec2 position_from_center = gl_FragCoord.xy / vec2(1366.f, 768.f) - vec2(0.5f);
	return smoothstep( 0.9, 0.05, length(position_from_center) );
}

void main(){

	vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
	float SSAO = texture(ssao, TexCoords).r;

	Diffuse *= SSAO;

	FragColor = vec4( mix( Diffuse, Diffuse * GetVignetteFactor(), 0.5f), 1.0f);
	return;
}
