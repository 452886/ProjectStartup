#ifndef TEXTUREMATERIAL_HPP
#define TEXTUREMATERIAL_HPP

#include "mge/materials/AbstractMaterial.hpp"
#include "GL/glew.h"

class ShaderProgram;
class Texture;

/**
 * This material is already a little bit more complicated, instead of a color we can pass in a texture,
 * all attributes and uniforms are cached and we precompute the MVP matrix passing it in as one entity.
 */
class TextureMaterial : public AbstractMaterial
{
public:
    TextureMaterial(Texture* pDiffuseTexture, Texture* pSpecularTexture, const float pShininess = 32.0f);
    virtual ~TextureMaterial();

    virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

    void setDiffuseTexture(Texture* pDiffuseTexture);
    void setSpecularTexture(Texture* pSpecularTexture);

protected:
private:
    static ShaderProgram* _shader;
    static void _lazyInitializeShader();

    //in this example we cache all identifiers for uniforms & attributes
    static GLint _uMVPMatrix;
    static GLint _uDiffuseTexture;
    static GLint _uSpecularTexture;

    static GLint _aVertex;
    static GLint _aNormal;
    static GLint _aUV;

    bool _hasSpecularTexture;

    Texture* _diffuseTexture;
    Texture* _specularTexture;

    const float _shininess;

    TextureMaterial(const TextureMaterial&);
    TextureMaterial& operator=(const TextureMaterial&);

    void addPointLight(int lightIndex, World* pWorld, int pointLightIndex);
    void addSpotLight(int lightIndex, World* pWorld, int spotLightIndex);
    void addDirLight(int lightIndex, World* pWorld, int dirLightIndex);
    void addAmbientLight(int lightIndex, World* pWorld, int ambientLightIndex);


};

#endif // TEXTUREMATERIAL_HPP
