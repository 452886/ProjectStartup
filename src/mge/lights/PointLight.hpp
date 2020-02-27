//#ifndef POINTLIGHT_HPP
//#define POINTLIGHT_HPP
//
//#include "mge/core/Light.hpp"
//
//class PointLight : public Light {
//	public:
//		PointLight(const std::string& pName = nullptr, const glm::vec3& pPosition = glm::vec3(0, 5, 0));
//		virtual ~PointLight();
//
//		// Getters/Setters
//		float& Constant() { return _constant; };
//		float& Linear() { return _linear; };
//		float& Quadratic() { return _quadratic; };
//
//		// Override 
//		LightType GetType();
//	private:
//		// light fall off
//		float _constant = 1.0f;
//		float _linear = 0.09f;
//		float _quadratic = 0.032f;
//
//};
//
//#endif // POINTLIGHT