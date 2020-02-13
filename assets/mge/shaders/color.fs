//DIFFUSE COLOR FRAGMENT SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1
out vec4 fragment_color;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 Normal;
in vec3 FragPos;

uniform float attenuation;
uniform vec3 viewPos;

uniform Material material;
uniform Light light;

void main( void ) {
	// ambient
	vec3 ambient = light.ambient * material.ambient;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	// specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	vec3 specular = light.specular * (spec * material.specular);

	float distanceToLight = length(light.position - FragPos);
	float attenuation = 1.0 / (1.0 + attenuation * pow(distanceToLight,2));

	vec3 result = (ambient + diffuse + specular)* attenuation;

	fragment_color = vec4(result,1.0);
	//fragment_color = vec4 (diffuseColor,1);
}
