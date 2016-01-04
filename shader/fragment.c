#version 330 core

in vec2 UV;
in vec3 colors;
out vec4 color;

uniform sampler2D myTexture;

void main(){
    vec2 inverted_UV = vec2(UV.x, 1-UV.y);
    
    vec4 tex = texture( myTexture, inverted_UV).rgba;
    if( tex.a < 0.1){
        discard;
    }
    //color = vec4(colors, 1) * tex;
    color = tex;
}
