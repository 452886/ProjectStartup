#pragma once
#include <vector>
#include <map>
#include "mge/nodegraph/Node.hpp";
#include <stdio.h>

class Nodegraph {
public:
	Nodegraph(std::vector<std::vector<sf::Vector2i>> nodeArray2D);
	void CreateNode(sf::Vector2i position);

private:
	std::vector<std::vector<sf::Vector2i>>* nodeArray2D;
	void Initialize();
};
