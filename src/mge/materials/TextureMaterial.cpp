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


ShaderProgram* TextureMaterial::_shader = NULL;

GLint TextureMaterial::_uMVPMatrix = 0;
GLint TextureMaterial::_uDiffuseTexture = 0;
GLint TextureMaterial::_uSpecularTexture = 0;

GLint TextureMaterial::_aVertex = 0;
GLint TextureMaterial::_aNormal = 0;
GLint TextureMaterial::_aUV = 0;

bool hasSpecularTexture = true;

TextureMaterial::TextureMaterial(Texture * pDiffuseTexture, Texture* pSpecularTexture):_diffuseTexture(pDiffuseTexture) {
	_specularTexture = pSpecularTexture;

	if (_specularTexture == nullptr) {
		hasSpecularTexture = false;
		std::cout << "has no specular" << std::endl;
	}

    _lazyInitializeShader();
}

TextureMaterial::~TextureMaterial() {}

void TextureMaterial::_lazyInitializeShader() {
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"texture.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"texture.fs");
        _shader->finalize();

        //cache all the uniform and attribute indexes
        _uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
        _uDiffuseTexture = _shader->getUniformLocation("diffuseTexture");
		_uSpecularTexture = _shader->getUniformLocation("specularTexture");

        _aVertex = _shader->getAttribLocation("vertex");
        _aNormal = _shader->getAttribLocation("normal");
        _aUV =     _shader->getAttribLocation("uv");
    }
}

void TextureMaterial::setDiffuseTexture (Texture* pDiffuseTexture) {
    _diffuseTexture = pDiffuseTexture;
}

void TextureMaterial::setSpecularTexture(Texture* pSpecularTexture)
{
	_specularTexture = pSpecularTexture;
}

void TextureMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
    if (!_diffuseTexture) return;

    _shader->use();

    //Print the number of lights in the scene and the position of the first light.
    //It is not used, but this demo is just meant to show you THAT materials can access the lights in a world
    //if (pWorld->getLightCount() > 0) {
    //    std::cout << "TextureMaterial has discovered light is at position:" << pWorld->getLightAt(0)->getLocalPosition() << std::endl;
    //}

    //setup texture slot 0
    glActiveTexture(GL_TEXTURE0);
    //bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
    //tell the shader the texture slot for the diffuse texture is slot 0
    glUniform1i (_uDiffuseTexture, 0);
	


	if (hasSpecularTexture) {
		glBindTexture(GL_TEXTURE_2D, _specularTexture->getId());
		glUniform1i(_uSpecularTexture, 2);
	}

	glUniform3fv(_shader->getUniformLocation("light.position"), 1, glm::value_ptr(pWorld->getLightAt(0)->getLocalPosition()));
	glUniform3fv(_shader->getUniformLocation("viewPos"), 1, glm::value_ptr(pWorld->getMainCamera()->getLocalPosition()));

	glm::vec3 lightColor = glm::vec3(1, 1, 1);

	glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
	glUniform3f(_shader->getUniformLocation("light.ambient"), ambientColor.r, ambientColor.g, ambientColor.b);
	glUniform3f(_shader->getUniformLocation("light.diffuse"), diffuseColor.r, diffuseColor.g, diffuseColor.b);
	glUniform3f(_shader->getUniformLocation("light.specular"), 1.0f, 1.0f, 1.0f);

	glUniform3f(_shader->getUniformLocation("material.ambient"), 1.0f, 0.5f, 0.31f);
	glUniform3f(_shader->getUniformLocation("material.diffuse"), 1.0f, 0.5f, 0.31f);
	glUniform3f(_shader->getUniformLocation("material.specular"), 0.5f, 0.5f, 0.5f);
	glUniform1f(_shader->getUniformLocation("material.shininess"), 32.0f);
	float attenuation = 0.0005f;

	glUniform1f(_shader->getUniformLocation("attenuation"), attenuation);

	//pass in all MVP matrices separately
	glUniformMatrix4fv(_shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(pViewMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));

    //now inform mesh of where to stream its data
    pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}
