#version 330 core

in vec2 TexCoords;
out float fragColor;

uniform sampler2D texInput;

uniform vec4 dirResRad;

void main() {

	vec2 dir = dirResRad.xy;
	float res = dirResRad.z;
	float radius = dirResRad.w;
	float blur = radius/res;
	float sum = 0.f;

	sum += texture(texInput, vec2(TexCoords.x - 4.0*blur*dir.x, TexCoords.y - 4.0*blur*dir.y)).r * 0.0162162162;
	sum += texture(texInput, vec2(TexCoords.x - 3.0*blur*dir.x, TexCoords.y - 3.0*blur*dir.y)).r * 0.0540540541;
	sum += texture(texInput, vec2(TexCoords.x - 2.0*blur*dir.x, TexCoords.y - 2.0*blur*dir.y)).r * 0.1216216216;
	sum += texture(texInput, vec2(TexCoords.x - 1.0*blur*dir.x, TexCoords.y - 1.0*blur*dir.y)).r * 0.1945945946;

	sum += texture(texInput, vec2(TexCoords.x, TexCoords.y)).r * 0.2270270270;

	sum += texture(texInput, vec2(TexCoords.x + 1.0*blur*dir.x, TexCoords.y + 1.0*blur*dir.y)).r * 0.1945945946;
	sum += texture(texInput, vec2(TexCoords.x + 2.0*blur*dir.x, TexCoords.y + 2.0*blur*dir.y)).r * 0.1216216216;
	sum += texture(texInput, vec2(TexCoords.x + 3.0*blur*dir.x, TexCoords.y + 3.0*blur*dir.y)).r * 0.0540540541;
	sum += texture(texInput, vec2(TexCoords.x + 4.0*blur*dir.x, TexCoords.y + 4.0*blur*dir.y)).r * 0.0162162162;

	fragColor = sum;
}
