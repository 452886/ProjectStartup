#ifndef SPOTLIGHT_HPP
#define SPOTLIGHT_HPP

#include "mge/core/Light.hpp"

class SpotLight : public Light {
public:
	SpotLight(const std::string& pName = nullptr, const glm::vec3& pPosition = glm::vec3(0, 5, 0));
	virtual ~SpotLight();

	// Getters/Setters
	

	float& Constant() & { return _constant; };
	float& Linear() & { return _linear; };
	float& Quadratic() & { return _quadratic; };

	glm::vec3& LDirection() { return _direction; };

	float& CutOff() { return _cutOff; };
	float& OuterCutOff() { return _outerCutOff; };

	// Override 
	LightType GetType();
private:
	// light fall off
	float _constant = 1.0f;
	float _linear = 0.09f;
	float _quadratic = 0.032f;

	glm::vec3 _direction = glm::vec3(0,-1,0);

	float _cutOff = glm::cos(glm::radians(12.5f));
	float _outerCutOff = glm::cos(glm::radians(17.5f));

};

#endif // SPOTLIGHT_HPP