#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 inputColors;
layout(location = 2) in vec2 textureCoords;

out vec2 UV;
out vec3 colors;

uniform mat4 MVP;
uniform vec2 TexRatio;
uniform vec2 TexShift;

void main(){

    vec4 v = vec4(vertexPosition, 1);
    gl_Position = MVP * v;
		UV = vec2(textureCoords.x, 1-textureCoords.y);
		if(TexRatio.x != -1){
			UV = (UV*TexRatio) + TexShift;
		}
    colors = inputColors;
}
