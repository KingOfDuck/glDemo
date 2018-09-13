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

uniform Material material;//����
uniform Light light;//����

in vec3 Normal;
in vec3 pos;

void main()
{
	//������

	//�����Դ���õ�ķ�������������������
	vec3 norm = normalize(Normal);//������������
	vec3 lightDir = normalize(light.position - pos);//��������������
	//����������
	float diff = max(dot(norm, lightDir), 0.0);//��ˣ��������ǿ��

	//�����ӵ㵽�õ�ķ�������
	vec3 viewDir = normalize(viewPos - pos);
	//���㷴������
	vec3 reflectDir = reflect(-lightDir, norm);
	//���㾵�����
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	vec3 result = light.diffuse * (diff * material.diffuse) + light.ambient * material.ambient\
		+ light.specular * (spec * material.specular);

    FragColor = vec4(result, 1.0);
}