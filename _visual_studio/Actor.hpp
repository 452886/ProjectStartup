#pragma once
#include "mge/core/GameObject.hpp";
#include <string>
#include "mge/nodegraph/Nodegraph.hpp"

class Actor : GameObject
{
public:
	Actor(Nodegraph& pNodeGraph);
	void MoveTowards(std::string node);
	void SetPosition(std::string node);

private:
	float movementSpeed;
	std::string currentNode;
	Nodegraph& nodegraph;
};

