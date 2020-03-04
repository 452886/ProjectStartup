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

void Nodegraph::addNode(std::string cords)
{
	nodes.push_back(cords);
}

bool Nodegraph::isWalkable(std::string cords)
{
	if (std::find(nodes.begin(), nodes.end(), cords) != nodes.end())
		return true;
	else
		return false;
}

