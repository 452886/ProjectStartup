#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Window/Keyboard.hpp>

KeysBehaviour::KeysBehaviour(float pMoveSpeed, float pTurnSpeed): AbstractBehaviour(), _moveSpeed(pMoveSpeed), _turnSpeed(pTurnSpeed)
{

}

KeysBehaviour::~KeysBehaviour()
{
}

void KeysBehaviour::update( float pStep )
{
	float moveSpeed = 0.0f; //default if no keys
	float turnSpeed = 0.0f;

	moveSpeed = _moveSpeed;

	glm::vec3 directionVector = glm::vec3(0, 0, 0);

	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W )) {
		directionVector += glm::vec3(0, 0, 1);
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S )) {
		directionVector += glm::vec3(0, 0, -1);
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D )) {
		directionVector += glm::vec3(1, 0, 0);
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A )) {
		directionVector += glm::vec3(-1, 0, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		directionVector += glm::vec3(0, 1, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
		directionVector += glm::vec3(0, -1, 0);
	}
	if (directionVector.x != 0 || directionVector.y != 0 || directionVector.z != 0) {
		directionVector = glm::normalize(directionVector);
		directionVector = directionVector * (moveSpeed * pStep);

		//translate the object in its own local space
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
			directionVector *= 0.2f;
		}
		_owner->translate(directionVector);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		_owner->rotate(pStep * glm::radians(-45.0f), glm::vec3(0, 1, 0.0f));

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		_owner->rotate(pStep * glm::radians(45.0f), glm::vec3(0, 1, 0.0f));
	}
}
