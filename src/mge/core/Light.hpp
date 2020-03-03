#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "glm.hpp"
#include "mge/core/GameObject.hpp"

/**
 * Exercise for the student: implement the Light class...
 * Imagine things like setLightType, setLightIntensity, setFalloffAngle etc, see the corresponding lectures
 */

enum class LightType {
	POINT = 0,
	SPOT,
	DIRECTION,
	AMBIENT
};

class Light : public GameObject
{
public:
	Light(const std::string& aName = nullptr, const LightType type = LightType::POINT, const glm::vec3& aPosition = glm::vec3(0, 5, 0));
	virtual ~Light();

	//override set parent to register/deregister light...
	virtual void _setWorldRecursively(World* pWorld) override;

	// get the light type
	LightType GetType();
	void SetLightType(LightType type);

	glm::vec3& Ambient() { return _ambient; };
	glm::vec3& Diffuse() { return _diffuse; };
	glm::vec3& Specular() { return _specular; };

	float& Constant() & { return _constant; };
	float& Linear() & { return _linear; };
	float& Quadratic() & { return _quadratic; };
	float& Range() { return _range; };


	glm::vec3& LDirection() { return _direction; };

	float& CutOff() { return _cutOff; };
	float& OuterCutOff() { return _outerCutOff; };


protected:

private:
	// Basic lighting properties
	glm::vec3 _ambient = glm::vec3(1, 1, 1);
	glm::vec3 _diffuse = glm::vec3(1, 1, 1);
	glm::vec3 _specular = glm::vec3(1, 1, 1);

	// light fall off
	float _constant = 1.0f;
	float _linear = 0.09f;
	float _quadratic = 0.032f;
	float _range = 1.0f;

	glm::vec3 _direction = glm::vec3(0, 0, 1);

	float _cutOff = glm::cos(glm::radians(12.5f));
	float _outerCutOff = glm::cos(glm::radians(17.5f));

	LightType _lightType;
};

#endif // LIGHT_HPP
