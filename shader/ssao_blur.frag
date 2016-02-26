#version 330 core

in vec2 TexCoords;
out float fragColor;

uniform sampler2D ssaoInput;
uniform vec2 dir;
uniform float resolution;

void main() {
	fragColor = texture2D(ssaoInput, TexCoords).r;
	return;

	float sum = 0.f;
	float radius = 10.f;
	float blur = radius/resolution;

	sum += texture2D(ssaoInput, vec2(TexCoords.x - 4.0*blur*dir.x, TexCoords.y - 4.0*blur*dir.y)).r * 0.0162162162;
	sum += texture2D(ssaoInput, vec2(TexCoords.x - 3.0*blur*dir.x, TexCoords.y - 3.0*blur*dir.y)).r * 0.0540540541;
	sum += texture2D(ssaoInput, vec2(TexCoords.x - 2.0*blur*dir.x, TexCoords.y - 2.0*blur*dir.y)).r * 0.1216216216;
	sum += texture2D(ssaoInput, vec2(TexCoords.x - 1.0*blur*dir.x, TexCoords.y - 1.0*blur*dir.y)).r * 0.1945945946;

	sum += texture2D(ssaoInput, vec2(TexCoords.x, TexCoords.y)).r * 0.2270270270;

	sum += texture2D(ssaoInput, vec2(TexCoords.x + 1.0*blur*dir.x, TexCoords.y + 1.0*blur*dir.y)).r * 0.1945945946;
	sum += texture2D(ssaoInput, vec2(TexCoords.x + 2.0*blur*dir.x, TexCoords.y + 2.0*blur*dir.y)).r * 0.1216216216;
	sum += texture2D(ssaoInput, vec2(TexCoords.x + 3.0*blur*dir.x, TexCoords.y + 3.0*blur*dir.y)).r * 0.0540540541;
	sum += texture2D(ssaoInput, vec2(TexCoords.x + 4.0*blur*dir.x, TexCoords.y + 4.0*blur*dir.y)).r * 0.0162162162;

	fragColor = sum;
}
