#pragma once
#include "glm.hpp"

class Node {
public:
	Node(int number, int x, int y, int z, int north, int east, int south, int west);
	glm::vec3 GetLocation();
	int North();
	int East();
	int South();
	int West();

private:
	int number;
	int x;
	int y;
	int z;

	int north;
	int east;
	int south;
	int west;
};