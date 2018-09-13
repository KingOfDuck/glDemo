#version 330 core
struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;//0.0f-128.0f
};
struct Light{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 color;
};
out vec4 FragColor;

uniform vec3 viewPos;

uniform Material material;//材质
uniform Light light;//光照

in vec3 Normal;
in vec3 pos;

void main()
{
	//环境光

	//计算光源到该点的方向向量（向量减法）
	vec3 norm = normalize(Normal);//正交化法向量
	vec3 lightDir = normalize(light.position - pos);//正交化方向向量
	//计算漫反射
	float diff = max(dot(norm, lightDir), 0.0);//点乘，漫反射光强度

	//计算视点到该点的方向向量
	vec3 viewDir = normalize(viewPos - pos);
	//计算反射向量
	vec3 reflectDir = reflect(-lightDir, norm);
	//计算镜面分量
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	vec3 result = light.diffuse * (diff * material.diffuse) + light.ambient * material.ambient\
		+ light.specular * (spec * material.specular);

    FragColor = vec4(result, 1.0);
}