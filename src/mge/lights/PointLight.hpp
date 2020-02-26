#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include "mge/core/Light.hpp"


class PointLight : public Light {
	public:
		PointLight(const std::string& pName = nullptr, const glm::vec3& pPosition = glm::vec3(0, 5, 0));
		virtual ~PointLight();

		// Basic lighting properties
		glm::vec3* _ambient;
		glm::vec3* _linear;
		glm::vec3* _quadratic;

	private:

};

#endif // POINTLIGHT