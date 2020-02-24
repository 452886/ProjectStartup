#pragma once
#include "Node.hpp"
#include "glm.hpp"

Node::Node(int number = 0, int x = 0, int y = 0, int z = 0, int north = -1, int east = -1, int south = -1, int west = -1) {
	this->number = number;
	this->x = x;
	this->y = y;
	this->north = north;
	this->east = east;
	this->south = south;
	this->west = west;
}

glm::vec3 Node::GetLocation() {
	return { glm::vec3(x, y, z) };
};

int Node::North() {
	return { north };
};
int Node::East() {
	return { east };
};
int Node::South() {
	return { south };
};
int Node::West() {
	return { west };
};