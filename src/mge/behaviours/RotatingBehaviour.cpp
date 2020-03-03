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
    //rotates 45° per second

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		_owner->rotate(pStep * glm::radians(0.1f), glm::vec3(0, 0, 1));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
		_owner->rotate(pStep * glm::radians(-0.1f), glm::vec3(0, 0, 1));
	}
}
