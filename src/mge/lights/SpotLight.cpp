#include "mge/lights/SpotLight.hpp"

SpotLight::SpotLight(const std::string& pName, const glm::vec3& pPosition) :Light(pName, pPosition)
{
}

SpotLight::~SpotLight()
{
}

LightType SpotLight::GetType()
{
	return LightType::SPOT;
}
