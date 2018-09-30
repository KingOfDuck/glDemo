#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 Tex;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

void main(){
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	FragPos = vec3(model * vec4(aPos,1.0));
	//法线矩阵，防止法线因不等比缩放产生偏差
	//Normal = mat3(transpose(inverse(model))) * aNormal;

	Normal = aNormal;
	TexCoords = Tex;
}