#version 330 core
out vec4 FragColor;


#define MAX_POINTLIGHT 16
#define MAX_SPOTLIGHT 16
#define MAX_TEXTURE_DIFF 8
#define MAX_TEXTURE_SPEC 8

struct Material{
	vec3 diffuse_color;
	vec3 specular_color;
	int useTexture;
	int nDiffuse;
	int nSpecular;
	sampler2D diffuse[MAX_TEXTURE_DIFF];
	sampler2D specular[MAX_TEXTURE_SPEC];
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

uniform vec3 viewPos;//当前视点
uniform vec3 viewDir;//相机方向
uniform Material material;//材质

uniform DirLight dirLight;//环境光
uniform PointLight pointLights[MAX_POINTLIGHT];//预先开辟点光源空间
uniform SpotLight spotLights[MAX_SPOTLIGHT];//预先开辟聚光空间

uniform int npointlight;//点光源数目
uniform int nspotlight;//聚光数目
uniform int hasdirlight;//是否有环境光

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

//函数声明
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 fragDir,
	vec3 tdiffuse, vec3 tspecular);//计算环境光
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 fragDir,
	vec3 tdiffuse, vec3 tspecular);//计算点光
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 fragDir,
	vec3 tdiffuse, vec3 tspecular);//计算聚光

void main(){
	vec3 norm = normalize(Normal);
    vec3 fragDir = normalize(viewPos - FragPos);
	
    vec3 result = vec3(0.0f,0.0f,0.0f);
	
	vec3 tdiffuse = vec3(0.0f);
	vec3 tspecular = vec3(0.0f);
	for(int i = 0; i < material.nDiffuse; i++){
		tdiffuse += vec3(texture(material.diffuse[i], TexCoords));
	}
	for(int i = 0; i < material.nSpecular; i++){
		tspecular += vec3(texture(material.specular[i], TexCoords));
	}

	if(hasdirlight == 1){
		result = CalcDirLight(dirLight, norm, fragDir, tdiffuse, tspecular);
	}
	for(int i = 0; i < npointlight; i++){
		result += CalcPointLight(pointLights[i], norm, FragPos, fragDir, tdiffuse, tspecular);    
	}
	for(int i = 0; i < nspotlight; i++){
		result += CalcSpotLight(spotLights[i], norm, FragPos, fragDir, tdiffuse, tspecular);  
	}

	FragColor = vec4(result, 1.0);
}


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 fragDir, 
	vec3 tdiffuse, vec3 tspecular){
	vec3 lightDir = normalize(-light.direction);
	float diff = abs(dot(normal, lightDir));

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(fragDir,reflectDir),0.0), material.shininess);

    vec3 ambient = light.ambient * tdiffuse;
    vec3 diffuse = light.diffuse * diff * tdiffuse;
    vec3 specular = light.specular * spec * tspecular;

	return (ambient + diffuse + specular);
}
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 fragDir, 
	vec3 tdiffuse, vec3 tspecular){
	vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(fragDir, reflectDir), 0.0), material.shininess);
    
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    
    vec3 ambient = light.ambient * tdiffuse * attenuation;
    vec3 diffuse = light.diffuse * diff * tdiffuse * attenuation;
    vec3 specular = light.specular * spec * tspecular * attenuation;

    return (ambient + diffuse + specular);
}
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 fragDir, 
	vec3 tdiffuse, vec3 tspecular){
	vec3 lpos, ldir;
	if(light.cameraSpot == 1){
		lpos = viewPos;
		ldir = viewDir;
	}else{
		lpos = light.position;
		ldir = light.direction;
	}
	vec3 lightDir = normalize(lpos - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(fragDir, reflectDir), 0.0), material.shininess);

    float distance = length(lpos - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	
	float theta = dot(lightDir, normalize(-ldir)); 
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	vec3 ambient = light.ambient * tdiffuse;
	vec3 diffuse = light.diffuse * diff * tdiffuse;
	vec3 specular = light.specular * spec * tspecular;
	
	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;

	return (ambient + diffuse + specular);
}