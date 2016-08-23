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

	vec3 lightPos = vec3(0, 5, 0);
	float linear = 0.001;
	float quadratic = 0.000;

	// Then calculate lighting as usual
	vec3 lighting = Albedo * 0.1; // hard-coded ambient component
	vec3 viewDir = normalize(viewPos - FragPos);

	// Diffuse
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Albedo; // * lights[i].Color;
	float dist= length(lightPos - FragPos);
	float attenuation = 1.0/(1.0+linear*dist + quadratic*dist*dist);
	lighting += diffuse*attenuation;

	FragColor = vec4(mix(lighting, lighting * GetVignetteFactor(), 0.5f), 1.0);


	//FragColor = vec4(1.0) - exp(-color * exposure);

	//if(gl_FragCoord.x < 1366.f/2.f){ FragColor = Bloom; return; }

	//Diffuse = mix(Diffuse, vec4(0.90f), 0.9);
	//Diffuse = mix(color, color * SSAO, 1.0);

	//FragColor = mix(Diffuse, Diffuse * GetVignetteFactor(), 0.5f);
	return;
}
