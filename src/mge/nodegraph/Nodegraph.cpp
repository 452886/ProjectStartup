#pragma once
#include <iostream>
#include <map>
#include <string>
#include <iterator>
#include <algorithm>
#include "mge/nodegraph/Nodegraph.hpp";
#include "mge/nodegraph/Node.hpp";
#include "glm.hpp";

Nodegraph::Nodegraph(std::vector<std::vector<sf::Vector2i>> pNodeArray2D)
{
	nodeArray2D = &pNodeArray2D;
}

void Nodegraph::Initialize()
{
}
