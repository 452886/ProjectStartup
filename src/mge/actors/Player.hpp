#include "mge/actors/Actor.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"

class Player : Actor {
public:
	Player(Nodegraph* pNodeGraph, KeysBehaviour* keyBehaviour);
	virtual void Update();
	void SetColor(int pColor);
	void ToggleVisibility(bool pIsVisible);
	void Take();
	void Die();

private:
	KeysBehaviour* keyBehaviour;
	Nodegraph* nodeGraph;
	int color;
	bool isVisible;
};