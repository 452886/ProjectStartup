#include "glm.hpp"

#include "TextureMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/config.hpp"
#include "mge/core/Camera.hpp"

#include <string>


ShaderProgram* TextureMaterial::_shader = NULL;

GLint TextureMaterial::_uMVPMatrix = 0;
GLint TextureMaterial::_uDiffuseTexture = 0;
GLint TextureMaterial::_uSpecularTexture = 0;

GLint TextureMaterial::_aVertex = 0;
GLint TextureMaterial::_aNormal = 0;
GLint TextureMaterial::_aUV = 0;

TextureMaterial::TextureMaterial(Texture* pDiffuseTexture, Texture* pSpecularTexture, const float pShininess) :_diffuseTexture(pDiffuseTexture), _specularTexture(pSpecularTexture), _shininess(pShininess) {
    _lazyInitializeShader();
}

TextureMaterial::~TextureMaterial() {}

void TextureMaterial::_lazyInitializeShader() {
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "texture.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "texture.fs");
        _shader->finalize();

        //cache all the uniform and attribute indexes
        _uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
        _uDiffuseTexture = _shader->getUniformLocation("material.diffuse");
        _uSpecularTexture = _shader->getUniformLocation("material.specular");

        _aVertex = _shader->getAttribLocation("vertex");
        _aNormal = _shader->getAttribLocation("normal");
        _aUV = _shader->getAttribLocation("uv");
    }
}


void TextureMaterial::setDiffuseTexture(Texture* pDiffuseTexture) {
    _diffuseTexture = pDiffuseTexture;
}

void TextureMaterial::setSpecularTexture(Texture* pSpecularTexture)
{
    _specularTexture = pSpecularTexture;
}

void TextureMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
    if (!_diffuseTexture) return;

    _shader->use();

    //setup texture slot 0
    glActiveTexture(GL_TEXTURE0);
    //bind the texture to the current active slot
    glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
    //tell the shader the texture slot for the diffuse texture is slot 0
    glUniform1i(_uDiffuseTexture, 0);

    // setup texture slot 1
    glActiveTexture(GL_TEXTURE1);
    //bind the texture to the current active slot
    glBindTexture(GL_TEXTURE_2D, _specularTexture->getId());
    //tell the shader the texture slot for the specular texture is slot 1
    glUniform1i(_uSpecularTexture, 1);

    glUniform3fv(_shader->getUniformLocation("viewPos"), 1, glm::value_ptr(pWorld->getMainCamera()->getLocalPosition()));
    glUniform1f(_shader->getUniformLocation("material.shininess"), _shininess);

    // ## LIGHTING STUFF

    glUniform1i(_shader->getUniformLocation("NumOffSpotLights"), pWorld->getLightTypeCount(LightType::SPOT));
    glUniform1i(_shader->getUniformLocation("NumOffPointLights"), pWorld->getLightTypeCount(LightType::POINT));
    glUniform1i(_shader->getUniformLocation("NumOffDirLights"), pWorld->getLightTypeCount(LightType::DIRECTION));
    glUniform1i(_shader->getUniformLocation("NumOffAmbientLights"), pWorld->getLightTypeCount(LightType::AMBIENT));

    //int totalNumOfLight = pWorld->getLightCount();

	for (int i = 0; i < pWorld->getLightTypeCount(LightType::SPOT); i++)
	{
		addSpotLight(i, pWorld);
	}
	for (int i = 0; i < pWorld->getLightTypeCount(LightType::POINT); i++)
	{
		addPointLight(i, pWorld);
	}
	for (int i = 0; i < pWorld->getLightTypeCount(LightType::DIRECTION); i++)
	{
		addDirLight(i, pWorld);
	}

    // ## ENDLIGHTING 

    //pass in all MVP matrices separately
    glUniformMatrix4fv(_shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
    glUniformMatrix4fv(_shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(pViewMatrix));
    glUniformMatrix4fv(_shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));

    //now inform mesh of where to stream its data
    pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}


void TextureMaterial::addPointLight(int index, World* pWorld)
{
    std::string localTypeIndex = std::to_string(index);

    glUniform3fv(_shader->getUniformLocation("pointLights[" + localTypeIndex + "].position"), 1, glm::value_ptr(pWorld->getPointLightAt(index)->getLocalPosition()));
    glUniform3fv(_shader->getUniformLocation("pointLights[" + localTypeIndex + "].ambient"), 1, glm::value_ptr(pWorld->getPointLightAt(index)->Ambient()));
    glUniform3fv(_shader->getUniformLocation("pointLights[" + localTypeIndex + "].diffuse"), 1, glm::value_ptr(pWorld->getPointLightAt(index)->Diffuse()));
    glUniform3fv(_shader->getUniformLocation("pointLights[" + localTypeIndex + "].specular"), 1, glm::value_ptr(pWorld->getPointLightAt(index)->Specular()));

    glUniform1f(_shader->getUniformLocation("pointLights[" + localTypeIndex + "].constant"), pWorld->getPointLightAt(index)->Constant());
    glUniform1f(_shader->getUniformLocation("pointLights[" + localTypeIndex + "].linear"), pWorld->getPointLightAt(index)->Linear());
    glUniform1f(_shader->getUniformLocation("pointLights[" + localTypeIndex + "].quadratic"), pWorld->getPointLightAt(index)->Quadratic());
}

void TextureMaterial::addSpotLight(int index, World* pWorld)
{
    std::string localTypeIndex = std::to_string(index);

	glUniform3fv(_shader->getUniformLocation("spotLights[" + localTypeIndex + "].position"), 1, glm::value_ptr(pWorld->getSpotLightAt(index)->getLocalPosition()));
	glUniform3fv(_shader->getUniformLocation("spotLights[" + localTypeIndex + "].direction"), 1, glm::value_ptr(pWorld->getSpotLightAt(index)->LDirection()));
	glUniform3fv(_shader->getUniformLocation("spotLights[" + localTypeIndex + "].ambient"), 1, glm::value_ptr(pWorld->getSpotLightAt(index)->Ambient()));
	glUniform3fv(_shader->getUniformLocation("spotLights[" + localTypeIndex + "].diffuse"), 1, glm::value_ptr(pWorld->getSpotLightAt(index)->Diffuse()));
	glUniform3fv(_shader->getUniformLocation("spotLights[" + localTypeIndex + "].specular"), 1, glm::value_ptr(pWorld->getSpotLightAt(index)->Specular()));

	glUniform1f(_shader->getUniformLocation("spotLights[" + localTypeIndex + "].constant"), pWorld->getSpotLightAt(index)->Constant());
	glUniform1f(_shader->getUniformLocation("spotLights[" + localTypeIndex + "].linear"), pWorld->getSpotLightAt(index)->Linear());
	glUniform1f(_shader->getUniformLocation("spotLights[" + localTypeIndex + "].quadratic"), pWorld->getSpotLightAt(index)->Quadratic());

	glUniform1f(_shader->getUniformLocation("spotLights[" + localTypeIndex + "].cutOff"), pWorld->getSpotLightAt(index)->CutOff());
	glUniform1f(_shader->getUniformLocation("spotLights[" + localTypeIndex + "].outerCutOff"), pWorld->getSpotLightAt(index)->OuterCutOff());

}

void TextureMaterial::addDirLight(int index, World* pWorld)
{
    std::string localTypeIndex = std::to_string(index);

	glUniform3fv(_shader->getUniformLocation("dirLights[" + localTypeIndex + "].direction"), 1, glm::value_ptr(pWorld->getDirLightAt(index)->LDirection()));
	glUniform3fv(_shader->getUniformLocation("dirLights[" + localTypeIndex + "].ambient"), 1, glm::value_ptr(pWorld->getDirLightAt(index)->Ambient()));
	glUniform3fv(_shader->getUniformLocation("dirLights[" + localTypeIndex + "].diffuse"), 1, glm::value_ptr(pWorld->getDirLightAt(index)->Diffuse()));
	glUniform3fv(_shader->getUniformLocation("dirLights[" + localTypeIndex + "].specular"), 1, glm::value_ptr(pWorld->getDirLightAt(index)->Specular()));
}

void TextureMaterial::addAmbientLight(int index, World* pWorld)
{
	std::string localTypeIndex = std::to_string(index);
}


