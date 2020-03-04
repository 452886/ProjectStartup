#pragma once
#include <vector>
#include <map>
#include "mge/nodegraph/Node.hpp";
#include <stdio.h>

class Nodegraph {
public:
	Nodegraph();
	void CreateNode(sf::Vector2i position);
	void SetNodeArray2D(std::vector<std::vector<sf::Vector2i>> nodeArray2D);

private:
	std::vector<std::vector<sf::Vector2i>>* nodeArray2D;
};
