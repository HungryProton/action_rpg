#version 330 core

in vec2 UV;
in vec3 colors;
out vec4 color;

uniform sampler2D myTexture;

void main(){
	vec4 tex = texture(myTexture, UV).rgba;
	if(tex.a == 0){
		discard;
	}
	color = vec4(colors, 1) * tex;
	color = tex;
}
