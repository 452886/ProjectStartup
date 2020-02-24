#include "NodeGraph.hpp"
#include <vector>;

NodeGraph::NodeGraph(std::vector<Node> arrayOfNodes) {
	this->arrayOfNodes = arrayOfNodes;
}

Node NodeGraph::GetNodeByIndex(int index) {
	return arrayOfNodes[index];
}
