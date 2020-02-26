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
	virtual ~Light();

	//override set parent to register/deregister light...
	virtual void _setWorldRecursively(World* pWorld) override;

	// get the light type
	virtual LightType GetType() = 0;

protected:
	Light(const std::string& aName = nullptr, const glm::vec3& aPosition = glm::vec3(0, 5, 0));

private:
};

#endif // LIGHT_HPP
