#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform float ambientStrength;//环境光强度
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform float specularStrenth;//高光强度

in vec3 Normal;
in vec3 pos;

void main()
{
	//环境光
	vec3 ambient = ambientStrength * lightColor;

	//计算光源到该点的方向向量（向量减法）
	vec3 norm = normalize(Normal);//正交化法向量
	vec3 lightDir = normalize(lightPos - pos);//正交化方向向量
	//计算漫反射
	float diff = max(dot(norm, lightDir), 0.0);//点乘，漫反射光强度
	vec3 diffuse = diff * lightColor;//漫反射光强

	//计算视点到该点的方向向量
	vec3 viewDir = normalize(viewPos - pos);
	//计算反射向量
	vec3 reflectDir = reflect(-lightDir, norm);
	//计算镜面分量，反光度取32次幂(2/4/8/16/32/64/...)
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

	vec3 result = (diffuse + ambient + specularStrenth * spec) * objectColor;
    FragColor = vec4(result, 1.0);
}