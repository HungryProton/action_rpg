#version 330 core

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec3 gAlbedoSpec;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D myTexture;

void main(){
	vec4 tex = texture(myTexture, TexCoords).rgba;
	if(tex.a == 0){
		discard;
	}

	gAlbedoSpec = tex.rgb;
	gPosition = FragPos;
	gNormal = normalize(Normal);
}
