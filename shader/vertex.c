#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 inputColors;
layout(location = 2) in vec2 textureCoords;

out vec2 UV;
out vec3 colors;

uniform mat4 MVP;

void main(){
    
    vec4 v = vec4(vertexPosition, 1);
    gl_Position = MVP * v;
    UV = textureCoords;
    colors = inputColors;
}
