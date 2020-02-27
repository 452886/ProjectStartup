#include "HoverBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Window/Keyboard.hpp>

HoverBehaviour::HoverBehaviour()
{
	int random = rand() % 2;
	if (random == 1)
		onSin = true;
	else
		onSin = false;
}

HoverBehaviour::~HoverBehaviour()
{
}

void HoverBehaviour::update(float pStep)
{
	stepCount += speed;

	float hoverHeight = 0;

	if (onSin)
		hoverHeight = (sin(stepCount) * 5);
	else 
		hoverHeight = (sin(stepCount) * 5);


	glm::vec3 directionVector = glm::vec3(0, hoverHeight, 0);

	_owner->translate(directionVector);
}
