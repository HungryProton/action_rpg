#version 330 core

layout (location = 0) out vec4 gPositionDepth;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
in float Alpha;

uniform sampler2D myTexture;

const float NEAR = 1.f;
const float FAR = 100.f;

float LinearizeDepth(float depth){
	float z = depth * 2.0 - 1.0; // Back to NDC
	return (2.0 * NEAR * FAR) / (FAR + NEAR - z * (FAR - NEAR));
}

void main(){
	vec4 tex = texture(myTexture, TexCoords).rgba;
	if(tex.a == 0){
		discard;
	}

	gAlbedoSpec = vec4(tex.rgb, Alpha);
	gPositionDepth.xyz = FragPos;
	gPositionDepth.a = LinearizeDepth(gl_FragCoord.z);
	gNormal = normalize(Normal);
}
