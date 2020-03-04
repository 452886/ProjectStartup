#pragma once
#include <vector>
#include "SFML/Graphics.hpp";
#include "Node.hpp";

Node::Node(sf::Vector2i pPosition)
{
	Position = pPosition;
}