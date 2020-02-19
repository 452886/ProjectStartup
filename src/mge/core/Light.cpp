#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"

Light::Light(const std::string& pName, const glm::vec3& aPosition, LightType aLightType, LightProperties aLightProperties) :GameObject(pName, aPosition), _type(aLightType), properties(aLightProperties)
{

}

Light::~Light() {

}

//Override setWorldRecursively to make sure we are registered
//to the world we are a part of.
void Light::_setWorldRecursively(World* pWorld) {

    //store the previous and new world before and after storing the given world
    World* previousWorld = _world;
    GameObject::_setWorldRecursively(pWorld);
    World* newWorld = _world;

    //check whether we need to register or unregister
    if (previousWorld != nullptr) previousWorld->unregisterLight(this);
    if (newWorld != nullptr) newWorld->registerLight(this);
}

LightType Light::Type()
{
    return _type;
}


LightProperties::LightProperties(glm::vec3& pAmbient, glm::vec3& pDiffuse, glm::vec3& pSpecular, float pConstant, float pLinear, float pQuadratic, glm::vec3& pDirection, float pCutOff, float pOuterCutOff)
{
    ambient = pAmbient;
    diffuse = pDiffuse;
    specular = pSpecular;

    constant = pConstant;
    linear = pLinear;
    quadratic = pQuadratic;

    direction = pDirection;

    cutOff = pCutOff;
    outerCutOff = pOuterCutOff;
}

LightProperties::~LightProperties()
{

}
