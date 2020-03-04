#pragma once
#include <string>
#include "mge/core/GameObject.hpp";
#include "mge/nodegraph/Nodegraph.hpp"

class Actor : public GameObject
{
public:
	Actor(Nodegraph* pNodeGraph);
	void MoveTowards(std::string node);
	void SetPosition(std::string node);
	std::string Position;

protected:
	float movementSpeed;
	std::string currentNode;
	Nodegraph* nodegraph;
};

