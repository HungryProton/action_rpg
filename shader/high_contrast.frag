#version 330 core

in vec2 TexCoords;
out vec4 fragColor;

uniform sampler2D texInput;
uniform vec2 threshold;

void main(){

	fragColor = vec4(0.0f);
	vec3 inputFrag = texture(texInput, TexCoords).rgb;
	// Check whether fragment output is higher than threshold, if so output as brightness color
	//float brightness = dot(inputFrag.rgb, vec3(1.1526, 0.3152, 0.0722));
	float brightness = 0;
	float t = 0.9;

	if(inputFrag.r >= t){ brightness += 1; }
	if(inputFrag.g >= t){ brightness += 1; }
	if(inputFrag.b >= t){ brightness += 1; }

	if(brightness >= 1.0)
		fragColor = vec4(inputFrag.rgb, 1.0);
}
