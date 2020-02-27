//#ifndef DIRLIGHT_HPP
//#define DIRLIGHT_HPP
//
//#include "mge/core/Light.hpp"
//
//class DirLight : public Light {
//public:
//	DirLight(const std::string& pName = nullptr, const glm::vec3& pPosition = glm::vec3(0, 5, 0));
//	virtual ~DirLight();
//
//	// Getters/Setters
//	glm::vec3& LDirection() { return _direction; };
//
//	// Override 
//	LightType GetType();
//private:
//	// light fall off
//	glm::vec3 _direction = glm::vec3(0, 0, -1);
//
//
//};
//
//#endif // DIRLIGHT_HPP