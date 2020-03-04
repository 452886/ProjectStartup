#pragma once
#include <iostream>
#include <map>
#include <string>
#include <iterator>
#include <algorithm>
#include "mge/nodegraph/Nodegraph.hpp";
#include "mge/nodegraph/Node.hpp";
#include "glm.hpp";

Nodegraph::Nodegraph()
{
}

void Nodegraph::SetNodeArray2D(std::vector<std::vector<sf::Vector2i>> nodeArray2D)
{
	this->nodeArray2D = &nodeArray2D;
}

void Nodegraph::CreateNode(sf::Vector2i position)
{
	nodeArray2D[position.x][position.y].push_back(position);

	std::cout << "x: " << position.x << " y: " << position.y << std::endl; 
}
