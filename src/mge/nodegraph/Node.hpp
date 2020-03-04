#pragma once
#include <vector>
#include "mge/core/GameObject.hpp";
#include "SFML/Graphics.hpp";


class Node
{
public:
	Node();
	sf::Vector2i Position;
	bool isActive;
};
