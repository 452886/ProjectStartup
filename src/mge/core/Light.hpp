#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "glm.hpp"
#include "mge/core/GameObject.hpp"

/**
 * Exercise for the student: implement the Light class...
 * Imagine things like setLightType, setLightIntensity, setFalloffAngle etc, see the corresponding lectures
 */


struct LightProperties {
	public :
		LightProperties(
			glm::vec3& pAmbient = glm::vec3(1, 1, 1),
			glm::vec3& pDiffuse = glm::vec3(1, 1, 1),
			glm::vec3& pSpecular = glm::vec3(1, 1, 1),

			float pConstant = 1,
			float pLinear = 0.09f,
			float pQuadratic = 0.032f,

			glm::vec3& pDirection = glm::vec3(1, 1, 1),

			float pCutOff = 1.0f,
			float pOuterCutOff = 10.0f
		);
		~LightProperties();

		glm::vec3 direction;
	
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		float cutOff;
		float outerCutOff;

		float constant;
		float linear;
		float quadratic;
};


enum class LightType {
	POINT = 0,
	SPOT,
	DIRECTION,
	AMBIENT
};

class Light : public GameObject
{
	public:
		Light(const std::string& aName = nullptr, const glm::vec3& aPosition = glm::vec3(2.0f, 10.0f, 5.0f), LightType aLightType = LightType::POINT, LightProperties aLightProperties = LightProperties());
		virtual ~Light();

        //override set parent to register/deregister light...
        virtual void _setWorldRecursively (World* pWorld) override;

		// get the light type
		LightType Type();
		LightProperties properties;

	protected:

	private:
		LightType _type;
};

#endif // LIGHT_HPP
