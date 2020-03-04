#include "mge/actors/Player.hpp";

Player::Player(Nodegraph* pNodeGraph, KeysBehaviour* pKeyBehaviour) : Actor(pNodeGraph)
{
	this->nodeGraph = pNodeGraph;

	addBehaviour(new KeysBehaviour(movementSpeed, 45.0f));
	keyBehaviour = dynamic_cast<KeysBehaviour*>(getBehaviour(0));
}

void Player::Update()
{
	if (keyBehaviour->keyDown('w')) {
		std::cout << "change da world" << std::endl;
	}
}

void Player::SetColor(int pColor) {
	this->color = pColor;
}

void Player::ToggleVisibility(bool pIsVisible)
{
	this->isVisible = pIsVisible;;
}
