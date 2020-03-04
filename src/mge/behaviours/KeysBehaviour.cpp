#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Window/Keyboard.hpp>

KeysBehaviour::KeysBehaviour(float pMoveSpeed, float pTurnSpeed, float pTileSize) : AbstractBehaviour(), _moveSpeed(pMoveSpeed), _turnSpeed(pTurnSpeed)
{
	tileSize = pTileSize;
	pressedKeys['w'] = false;
	pressedKeys['a'] = false;
	pressedKeys['s'] = false;
	pressedKeys['d'] = false;
}

KeysBehaviour::~KeysBehaviour()
{
}

void KeysBehaviour::update(float pStep)
{
	float moveSpeed = 0.0f; //default if no keys
	float turnSpeed = 0.0f;
	updatePressedKeys();


}

void KeysBehaviour::updatePressedKeys()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		pressedKeys['w'] = true;
	}
	else {
		pressedKeys['w'] = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		pressedKeys['s'] = true;
	}
	else {
		pressedKeys['s'] = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		pressedKeys['d'] = true;
	}
	else {
		pressedKeys['d'] = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		pressedKeys['a'] = true;
	}
	else {
		pressedKeys['a'] = false;
	}
}

bool KeysBehaviour::keyDown(char key)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(key)))
	{
		if (pressedKeys[key] != true)
		{
			return true;
			pressedKeys[key] = true;
		}
	}
	return false;
}
