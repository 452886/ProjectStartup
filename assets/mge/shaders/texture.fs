//DIFFUSE TEXTURE FRAGMENT SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

// Outgoing color of this fragment instance
out vec4 fragment_color;


struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

// Point Light
struct PointLight
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
uniform PointLight pointLight;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

void main( void ) {
	// Getting the textures colors for this frag
	vec3 matDiffuse = vec3(texture(material.diffuse,texCoord));
	vec3 matSpecular = vec3(texture(material.specular,texCoord));

	// ambient
	vec3 ambient = pointLight.ambient * matDiffuse;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(pointLight.position - FragPos);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = pointLight.diffuse * diff * matDiffuse;

	// specular
	float specularStrenght = 1;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	vec3 specular = pointLight.specular * spec * matSpecular;

	// Calculate the light attenuation ( the falloff over distance of light )
	float distanceToLight = length(pointLight.position - FragPos);
	float attenuation = 1.0 / (1.0 + attenuation * pow(distanceToLight,2));

	vec3 result = (ambient + diffuse + specular) * attenuation;

	fragment_color = vec4(result,1.0);
	
	//fragment_color = texture(diffuseTexture,texCoord);
}
