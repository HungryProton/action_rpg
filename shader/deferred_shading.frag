#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D gPositionDepth;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;
uniform sampler2D ssao;
uniform sampler2D bloom;
uniform sampler2D flare;
uniform vec3 viewPos;

const int NB_LIGHTS = 12;
uniform float[NB_LIGHTS] lightsIntensity;
uniform vec3[NB_LIGHTS] lightsPos;

float GetVignetteFactor(){
	vec2 position_from_center = gl_FragCoord.xy / vec2(1366.f, 768.f) - vec2(0.5f);
	return smoothstep( 0.9, 0.05, length(position_from_center) );
}

void main(){

	vec3 FragPos = texture(gPositionDepth, TexCoords).rgb;
	vec3 Normal = texture(gNormal, TexCoords).rgb;
	vec3 Albedo = texture(gAlbedoSpec, TexCoords).rgb;
	float SSAO = texture(ssao, TexCoords).r;
	vec4 Bloom = texture(bloom, TexCoords).rgba;
	vec4 Flare = texture(flare, TexCoords).rgba;
	float exposure = 1.0;
	//vec4 color = Albedo + Bloom * Bloom + (Flare*2);

	float linear = 0;
	float quadratic = 0;

	vec3 lighting = Albedo * 0.15; // hard-coded ambient component
	vec3 viewDir = normalize(FragPos);

	for(int i = 0; i < NB_LIGHTS; i++){
		if(lightsIntensity[i] == 0){ continue; }
		// Diffuse
		vec3 lightDir = normalize(lightsPos[i] - FragPos);
		vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Albedo; // * lights[i].Color;
		float dist= length(lightsPos[i] - FragPos);
		if(dist <= 10){
			float attenuation = 1.0/(1.0+linear*dist + quadratic*dist*dist);
			lighting += diffuse*attenuation*lightsIntensity[i];
		}else{
			lighting += 0;
		}
	}

	FragColor = vec4(mix(lighting, lighting * GetVignetteFactor(), 0.5f), 1.0);


	//FragColor = vec4(1.0) - exp(-color * exposure);

	//if(gl_FragCoord.x < 1366.f/2.f){ FragColor = Bloom; return; }

	//Diffuse = mix(Diffuse, vec4(0.90f), 0.9);
	//Diffuse = mix(color, color * SSAO, 1.0);

	//FragColor = mix(Diffuse, Diffuse * GetVignetteFactor(), 0.5f);
	return;
}
