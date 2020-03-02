//DIFFUSE TEXTURE FRAGMENT SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

#define MAX_NUMBER_OF_SPOT_LIGHTS 30
#define MAX_NUMBER_OF_POINT_LIGHTS 30
#define MAX_NUMBER_OF_DIR_LIGHTS 30
#define MAX_NUMBER_OF_AMBIENT_LIGHTS 30

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct DirLight
{
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;
        
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float range;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;
    
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	float cutOff;
    float outerCutOff;
    
    float constant;
    float linear;
    float quadratic;
    
    float range;
};

struct AmbientLight
{
	vec3 diffuse;
	float strenght;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 texCoord;

// Outgoing color of this fragment instance
out vec4 fragment_color;

uniform int NumOffSpotLights;
uniform int NumOffPointLights;
uniform int NumOffDirLights;
uniform int NumOffAmbientLights;

uniform vec3 viewPos;

uniform DirLight dirLights[MAX_NUMBER_OF_DIR_LIGHTS];
uniform PointLight pointLights[MAX_NUMBER_OF_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_NUMBER_OF_SPOT_LIGHTS];
uniform AmbientLight ambientLights[MAX_NUMBER_OF_AMBIENT_LIGHTS];
uniform Material material;

// Function prototypes
vec3 CalcDirLight( DirLight light, vec3 normal, vec3 viewDir );
vec3 CalcPointLight( PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir );
vec3 CalcSpotLight( SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir );

void main( )
{
    // Properties
    vec3 norm = normalize( Normal );
    vec3 viewDir = normalize( viewPos - FragPos );
    
    // Directional lighting
    vec3 result = vec3(0,0,0);

	for (int i = 0; i < NumOffDirLights; i++)
	{
		result += CalcDirLight( dirLights[i], norm, viewDir );
	}

    // Point lights
    for ( int i = 0; i < NumOffPointLights; i++ )
    {
        result += CalcPointLight( pointLights[i], norm, FragPos, viewDir );
    }

    // Spot light
	for (int i = 0; i < NumOffSpotLights; i++)
	{
    	result += CalcSpotLight( spotLights[i], norm, FragPos, viewDir );
	}

    //Emission
    vec3 emission = vec3(texture(material.emission,texCoord));
    
    result += emission;

    fragment_color = vec4( result, 1.0 );
}

// Calculates the color when using a directional light.
vec3 CalcDirLight( DirLight light, vec3 normal, vec3 viewDir )
{
    vec3 lightDir = normalize( -light.direction );
    
    // Diffuse shading
    float diff = max( dot( normal, lightDir ), 0.0 );
    
    // Specular shading
    vec3 reflectDir = reflect( -lightDir, normal );
    float spec = pow( max( dot( viewDir, reflectDir ), 0.0 ), material.shininess );
    
    // Combine results
    vec3 ambient = light.ambient * vec3( texture( material.diffuse, texCoord ) );
    vec3 diffuse = light.diffuse * diff * vec3( texture( material.diffuse, texCoord ) );
    vec3 specular = light.specular * spec * vec3( texture( material.specular, texCoord ) );
    
    return ( ambient + diffuse + specular );
}

// Calculates the color when using a point light.
vec3 CalcPointLight( PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir )
{
    vec3 lightDir = normalize( light.position - fragPos );
    
    // Diffuse shading
    float diff = max( dot( normal, lightDir ), 0.0 );
    
    // Specular shading
    vec3 reflectDir = reflect( -lightDir, normal );
    float spec = pow( max( dot( viewDir, reflectDir ), 0.0 ), material.shininess );
    
    // Attenuation
    float distance = length( light.position - fragPos );
    float attenuation = 1.0f / ( light.constant + light.linear * distance + light.quadratic * ( distance * distance ) );
    
    // Combine results
    vec3 ambient = light.ambient * vec3( texture( material.diffuse, texCoord ) );
    vec3 diffuse = light.diffuse * diff * vec3( texture( material.diffuse, texCoord ) );
    vec3 specular = light.specular * spec * vec3( texture( material.specular, texCoord ) );
    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    return ( ambient + diffuse + specular );
}

// Calculates the color when using a spot light.
vec3 CalcSpotLight( SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir )
{
    vec3 lightDir = normalize( light.position - fragPos );
    
    // Diffuse shading
    float diff = max( dot( normal, lightDir ), 0.0 );
    
    // Specular shading
    vec3 reflectDir = reflect( -lightDir, normal );
    float spec = pow( max( dot( viewDir, reflectDir ), 0.0 ), material.shininess );
    
    // Attenuation
    float distance = length( light.position - fragPos );
    float attenuation = 1.0f / ( light.constant + light.linear * distance + light.quadratic * ( distance * distance ) );
    
    // Spotlight intensity
    float theta = dot( lightDir, normalize( -light.direction ) );
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp( ( theta - light.outerCutOff ) / epsilon, 0.0, 1.0 );
    
    // Combine results
    vec3 ambient = light.ambient * vec3( texture( material.diffuse, texCoord ) );
    vec3 diffuse = light.diffuse * diff * vec3( texture( material.diffuse, texCoord ) );
    vec3 specular = light.specular * spec * vec3( texture( material.specular, texCoord ) );
    
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    
    return ( ambient + diffuse + specular );
}