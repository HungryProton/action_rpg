#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D gPositionDepth;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;
uniform sampler2D ssao;

void main(){

	vec3 FragPos = texture(gPositionDepth, TexCoords).rgb;
	vec3 Diffuse1 = texture(gAlbedoSpec, TexCoords).rgb;

	FragColor = vec4( Diffuse1 * texture(ssao, TexCoords).r, 1.0f);
	//FragColor = vec4( vec3(0.90f) * texture(ssao, TexCoords).r, 1.0f);
	return;

	vec2 res = vec2(1366.f, 768.f);

	if(gl_FragCoord.x < res.x/2.f){

		// TOP LEFT
		if(gl_FragCoord.y > res.y/2.f){
			float ssao = texture(ssao, TexCoords*2.f).r;
			FragColor = vec4(vec3(0.90)*ssao, 1.0f);

		// BOTTOM LEFT
		} else {
			vec3 Normal = texture(gNormal, vec2(TexCoords.x*2.f, (TexCoords.y - 0.5f)*2.f)).rgb;
			FragColor = vec4(Normal, 1.0f);
		}
	} else {

		// TOP RIGHT
		if(gl_FragCoord.y > res.y/2.f){
			vec3 Depth = vec3( texture(gPositionDepth, vec2((TexCoords.x-0.5f)*2.f, (TexCoords.y-0.5f)*2.f)).a/100.f);
			FragColor = vec4(Depth, 1.0f);

		// BOTTOM RIGHT
		} else {
			vec3 Position = texture(gPositionDepth, vec2((TexCoords.x-0.5f)*2.f, TexCoords.y*2.f)).rgb;
			FragColor = vec4(Position, 1.0f);
		}
	}
}
