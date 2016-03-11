#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D gPositionDepth;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;
uniform sampler2D ssao;
uniform sampler2D bloom;
uniform sampler2D flare;

float GetVignetteFactor(){
	vec2 position_from_center = gl_FragCoord.xy / vec2(1366.f, 768.f) - vec2(0.5f);
	return smoothstep( 0.9, 0.05, length(position_from_center) );
}

void main(){

	vec4 Diffuse = texture(gAlbedoSpec, TexCoords).rgba;
	float SSAO = texture(ssao, TexCoords).r;
	vec4 Bloom = texture(bloom, TexCoords).rgba;
	vec4 Flare = texture(flare, TexCoords).rgba;
	float exposure = 1.0;
	vec4 color = Diffuse + Bloom * Bloom + (Flare*2);

	FragColor = vec4(1.0) - exp(-color * exposure);

	//if(gl_FragCoord.x < 1366.f/2.f){ FragColor = Bloom; return; }

	//Diffuse = mix(Diffuse, vec4(0.90f), 0.9);
	Diffuse = mix(color, color * SSAO, 1.0);
	//Diffuse *= SSAO;

	FragColor = mix( Diffuse, Diffuse * GetVignetteFactor(), 0.5f);
	return;
}
