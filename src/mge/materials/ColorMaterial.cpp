#include "glm.hpp"

#include "ColorMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"


ShaderProgram* ColorMaterial::_shader = NULL;

ColorMaterial::ColorMaterial(glm::vec3 pDiffuseColor):_diffuseColor (pDiffuseColor)
{
    //every time we create an instance of colormaterial we check if the corresponding shader has already been loaded
    _lazyInitializeShader();
}

void ColorMaterial::_lazyInitializeShader() {
    //this shader contains everything the material can do (it can render something in 3d using a single color)
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"color.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"color.fs");
        _shader->finalize();
    }
}

ColorMaterial::~ColorMaterial()
{
    //dtor
}

void ColorMaterial::setDiffuseColor(glm::vec3 pDiffuseColor) {
    _diffuseColor = pDiffuseColor;
}

void ColorMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
    _shader->use();

    //set the material color
	glUniform3fv(_shader->getUniformLocation("light.position"), 1, glm::value_ptr(pWorld->getLightAt(0)->getLocalPosition()));
	glUniform3fv(_shader->getUniformLocation("viewPos"), 1, glm::value_ptr(pWorld->getMainCamera()->getLocalPosition()));

	glm::vec3 lightColor = glm::vec3(1, 1, 1);

	glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
	glUniform3f(_shader->getUniformLocation("light.ambient"), ambientColor.r, ambientColor.g, ambientColor.b);
	glUniform3f(_shader->getUniformLocation("light.diffuse"), diffuseColor.r, diffuseColor.g, diffuseColor.b);
	glUniform3f(_shader->getUniformLocation("light.specular"), 1.0f,1.0f,1.0f);

	glUniform3f(_shader->getUniformLocation("material.ambient"), 1.0f, 0.5f, 0.31f);
	glUniform3f(_shader->getUniformLocation("material.diffuse"), 1.0f, 0.5f, 0.31f);
	glUniform3f(_shader->getUniformLocation("material.specular"), 0.5f, 0.5f, 0.5f);
	glUniform1f(_shader->getUniformLocation("material.shininess"), 32.0f);

	float attenuation = 0.0005f;
	glUniform1f(_shader->getUniformLocation("attenuation"), attenuation);

    //pass in all MVP matrices separately
    glUniformMatrix4fv ( _shader->getUniformLocation("projectionMatrix"),   1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
    glUniformMatrix4fv ( _shader->getUniformLocation("viewMatrix"),         1, GL_FALSE, glm::value_ptr(pViewMatrix));
    glUniformMatrix4fv ( _shader->getUniformLocation("modelMatrix"),        1, GL_FALSE, glm::value_ptr(pModelMatrix));

    //now inform mesh of where to stream its data
    pMesh->streamToOpenGL(
        _shader->getAttribLocation("position"),
        _shader->getAttribLocation("normal"),
        _shader->getAttribLocation("uv")
    );

}
