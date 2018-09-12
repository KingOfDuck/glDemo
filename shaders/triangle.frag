#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform float ambientStrength;//������ǿ��
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform float specularStrenth;//�߹�ǿ��

in vec3 Normal;
in vec3 pos;

void main()
{
	//������
	vec3 ambient = ambientStrength * lightColor;

	//�����Դ���õ�ķ�������������������
	vec3 norm = normalize(Normal);//������������
	vec3 lightDir = normalize(lightPos - pos);//��������������
	//����������
	float diff = max(dot(norm, lightDir), 0.0);//��ˣ��������ǿ��
	vec3 diffuse = diff * lightColor;//�������ǿ

	//�����ӵ㵽�õ�ķ�������
	vec3 viewDir = normalize(viewPos - pos);
	//���㷴������
	vec3 reflectDir = reflect(-lightDir, norm);
	//���㾵������������ȡ32����(2/4/8/16/32/64/...)
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

	vec3 result = (diffuse + ambient + specularStrenth * spec) * objectColor;
    FragColor = vec4(result, 1.0);
}