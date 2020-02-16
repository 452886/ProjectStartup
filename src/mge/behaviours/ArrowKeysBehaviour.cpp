#include "mge/behaviours/ArrowKeysBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Window/Keyboard.hpp>

ArrowKeysBehaviour::ArrowKeysBehaviour(float pMoveSpeed, float pTurnSpeed) : AbstractBehaviour(), _moveSpeed(pMoveSpeed), _turnSpeed(pTurnSpeed)
{
}

ArrowKeysBehaviour::~ArrowKeysBehaviour()
{
}

void ArrowKeysBehaviour::update(float pStep)
{
	float moveSpeed = 0.0f; //default if no keys
	float turnSpeed = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		moveSpeed = _moveSpeed * 20;
	else
		moveSpeed = _moveSpeed;


	glm::vec3 directionVector = glm::vec3(0, 0, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		directionVector += glm::vec3(0, 0, -1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		directionVector += glm::vec3(0, 0, 1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		directionVector += glm::vec3(1, 0, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		directionVector += glm::vec3(-1, 0, 0);
	}
	if (directionVector.x != 0 || directionVector.y != 0 || directionVector.z != 0) {
		directionVector = glm::normalize(directionVector);
		directionVector = directionVector * (moveSpeed * pStep);

		//translate the object in its own local space
		_owner->translate(directionVector);
	}

	//we can also translate directly, basically we take the z axis from the matrix
	//which is normalized and multiply it by moveSpeed*step, then we add it to the
	//translation component
	//glm::mat4 transform = _owner->getTransform();
	//transform[3] += transform[2] * moveSpeed*pStep;
	//_owner->setTransform(transform);

	//rotate the object in its own local space

	// * _owner->rotate( glm::radians(turnSpeed*pStep), glm::vec3(0.0f, 1.0f, 0.0f ) ); *

	//NOTE:
	//The reason the above happens in the local space of the object and not in the world space
	//is that we use the _owner->translate / rotate shortcuts which in turn call glm::rotate / glm::translate
	//The methods multiply the current transform with the translation/rotation matrix from left to right
	//meaning everything happens in local space.
}
