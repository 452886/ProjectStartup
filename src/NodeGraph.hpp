#pragma once
#include "Node.hpp"
#include <vector>;

class NodeGraph
{
public:
	NodeGraph(std::vector<Node> arrayOfNodes);
	Node GetNodeByIndex(int index);

private:
	std::vector<Node> arrayOfNodes;
};

