//DIFFUSE COLOR VERTEX SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec3 position;
in vec3 normal;
in vec2 uv;

out vec3 Normal;
out vec3 FragPos;

uniform	mat4 	projectionMatrix;
uniform	mat4 	viewMatrix;
uniform	mat4 	modelMatrix;

void main( void ){
    	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.f);
		FragPos = vec3(modelMatrix * vec4(position,1.0f));
		Normal = mat3(transpose(inverse(modelMatrix))) * normal;
}
