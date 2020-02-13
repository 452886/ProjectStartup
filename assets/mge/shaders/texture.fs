//DIFFUSE TEXTURE FRAGMENT SHADER
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

in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;

uniform float attenuation;
uniform vec3 viewPos;

uniform Material material;
uniform Light light;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

void main( void ) {
	// ambient
	float ambientStrenght = 0.1f;
	vec3 ambient = ambientStrenght * light.diffuse;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = diff * light.diffuse;

	// specular
	float specularStrenght = 1;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	vec3 specular = light.specular * (spec * material.specular);	

	vec4 textureColor = texture(diffuseTexture,texCoord);

	float distanceToLight = length(light.position - FragPos);
	float attenuation = 1.0 / (1.0 + attenuation * pow(distanceToLight,2));

	vec3 result = ((ambient + diffuse + specular)* attenuation) * vec3(textureColor.x,textureColor.y,textureColor.z);

	fragment_color = vec4(result,1.0);
	
	//fragment_color = texture(diffuseTexture,texCoord);
}
