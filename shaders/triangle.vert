#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec3 Normal;
out vec3 pos;

void main(){
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	pos = vec3(model * vec4(aPos,1.0));
	//法线矩阵，防止法线因不等比缩放产生偏差
	//Normal = mat3(transpose(inverse(model))) * aNormal;

	Normal = aNormal;
}