#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Window/Keyboard.hpp>


RotatingBehaviour::RotatingBehaviour():AbstractBehaviour()
{
	//ctor
}

RotatingBehaviour::~RotatingBehaviour()
{
	//dtor
}

void RotatingBehaviour::update(float pStep)
{
	_owner->rotate(pStep * glm::radians(60.0f), glm::vec3(0, 1, 0));
}
