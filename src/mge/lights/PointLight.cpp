#include "mge/lights/PointLight.hpp"

PointLight::PointLight(const std::string& aName, const glm::vec3& aPosition) :Light(aName,aPosition)
{

}

PointLight::~PointLight()
{

}

LightType PointLight::GetType()
{
	return LightType::POINT;
}
