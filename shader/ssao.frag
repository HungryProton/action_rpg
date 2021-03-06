#version 330 core

out float FragColor;
in vec2 TexCoords;

uniform sampler2D gPositionDepth;
uniform sampler2D gNormal;
uniform sampler2D texNoise;
uniform sampler1D samples;

uniform mat4 projection;
uniform int kernelSize;

// tile noise texture over screen based on screen dimensions divided by
// noise size

const vec2 noiseScale = vec2(1366.0/4.0, 768.0/4.0);
float radius = 2.f;

void main()
{
	vec3 fragPos = texture(gPositionDepth, TexCoords).rgb;
	vec3 normal = texture(gNormal, TexCoords).rgb;
	vec3 randomVec = texture(texNoise, TexCoords * noiseScale).xyz;
	vec3 tangent = normalize(randomVec - normal * dot(randomVec, normal));
	vec3 bitangent = cross(normal, tangent);
	mat3 TBN = mat3(tangent, bitangent, normal);

	float occlusion = 0.0;
	for(float i = 0; i < kernelSize; i++){
		vec3 sample = TBN * texture(samples, i).rgb;
		sample = fragPos + sample * radius;
		vec4 offset = vec4(sample, 1.0);
		offset = projection * offset; // from view to clip-space
		offset.xyz /= offset.w; // perspective divide
		offset.xyz = offset.xyz * 0.5 + 0.5; // transform to range 0.0 - 1.0
		float sampleDepth = -texture(gPositionDepth, offset.xy).a;
		float rangeCheck = smoothstep(0.0, 1.0, radius / abs(fragPos.z - sampleDepth)) * 0.3f;
		occlusion += (sampleDepth >= sample.z ? 1.0 : 0.0) * rangeCheck;
	}
	occlusion = 1.0 - (occlusion / float(kernelSize));
	FragColor = occlusion*occlusion;
}
