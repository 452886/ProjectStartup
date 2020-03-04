#pragma once
#include <vector>
#include <map>
#include "mge/nodegraph/Node.hpp";
#include <stdio.h>

class Nodegraph {
public:
	Nodegraph();

	void addNode(std::string cords);
	bool isWalkable(std::string cords);

private:
	std::vector<std::string> nodes;
};
