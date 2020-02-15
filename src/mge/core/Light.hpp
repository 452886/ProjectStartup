#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "glm.hpp"
#include "mge/core/GameObject.hpp"

/**
 * Exercise for the student: implement the Light class...
 * Imagine things like setLightType, setLightIntensity, setFalloffAngle etc, see the corresponding lectures
 */

enum LType {
	POINT = 0,
	SPOT,
	DIRECTION,
	AMBIENT
};

class Light : public GameObject
{
	public:
		Light(const std::string& aName = nullptr, const LType aLightType = POINT, const glm::vec3& aPosition = glm::vec3( 2.0f, 10.0f, 5.0f ), const glm::vec3& aColor = glm::vec3(1,1,1));
		virtual ~Light();

        //override set parent to register/deregister light...
        virtual void _setWorldRecursively (World* pWorld) override;
		glm::vec3 getColor();

		// get the light 

	private:
		glm::vec3 _lightColor;
		LType _lType;
};

#endif // LIGHT_HPP
