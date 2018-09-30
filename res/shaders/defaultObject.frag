#version 330 core
out vec4 FragColor;

struct Material{
	vec3 diffuse_color;
	vec3 specular_color;
	int useTexture;
	sampler2D diffuse;
	sampler2D specular;
	float shininess;//0.0f-128.0f
};

struct DirLight{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight{
	vec3 position;
	float constant;
	float linear;
	float quadratic;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight{
	vec3 position;
	vec3 direction;
	int cameraSpot;
	float constant;
	float linear;
	float quadratic;
	float cutOff;
	float outerCutOff;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

#define MAX_POINTLIGHT 16
#define MAX_SPOTLIGHT 16

uniform vec3 viewPos;//��ǰ�ӵ�
uniform vec3 viewDir;//�������
uniform Material material;//����

uniform DirLight dirLight;//������
uniform PointLight pointLights[MAX_POINTLIGHT];//Ԥ�ȿ��ٵ��Դ�ռ�
uniform SpotLight spotLights[MAX_SPOTLIGHT];//Ԥ�ȿ��پ۹�ռ�

uniform int npointlight;//���Դ��Ŀ
uniform int nspotlight;//�۹���Ŀ
uniform int hasdirlight;//�Ƿ��л�����

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

//��������
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 fragDir);//���㻷����
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 fragDir);//������
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 fragDir);//����۹�

void main(){
	vec3 norm = normalize(Normal);
    vec3 fragDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0f,0.0f,0.0f);
	if(hasdirlight == 1){
		result = CalcDirLight(dirLight, norm, fragDir);
	}

	for(int i = 0; i < npointlight; i++){
		result += CalcPointLight(pointLights[i], norm, FragPos, fragDir);    
	}
	for(int i = 0; i < nspotlight; i++){
		result += CalcSpotLight(spotLights[i], norm, FragPos, fragDir);  
	}
	FragColor = vec4(result, 1.0);
}


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 fragDir){
	vec3 lightDir = normalize(-light.direction);
	float diff = abs(dot(normal, lightDir));

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(fragDir,reflectDir),0.0), material.shininess);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

	return (ambient + diffuse + specular);
}
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 fragDir){
	vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir),0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(fragDir, reflectDir), 0.0), material.shininess);
    
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords)) * attenuation;
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords)) * attenuation;
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords)) * attenuation;

    return (ambient + diffuse + specular);
}
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 fragDir){
	vec3 lpos, ldir;
	if(light.cameraSpot == 1){
		lpos = viewPos;
		ldir = viewDir;
	}else{
		lpos = light.position;
		ldir = light.direction;
	}
	vec3 lightDir = normalize(lpos - fragPos);
    float diff = abs(dot(normal, lightDir));

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(fragDir, reflectDir), 0.0), material.shininess);

    float distance = length(lpos - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	
	float theta = dot(lightDir, normalize(-ldir)); 
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	
	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;

	return (ambient + diffuse + specular);
}