#version 330 core
out vec4 fcol;
	
in vec3 Color;
in vec2 Tex;

uniform sampler2D tex;
uniform sampler2D tex2;


void main(){
	fcol = mix(texture(tex,Tex),texture(tex2,Tex),0.2);
}