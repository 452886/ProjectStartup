#ifndef HOVERBEHAVIOUR_HPP
#define HOVERBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"

class HoverBehaviour : public AbstractBehaviour
{
public:
	HoverBehaviour();
	virtual ~HoverBehaviour();

	virtual void update(float pStep);

private:
	float stepCount = 0;
	float speed = 0.1f;

	bool onSin;
};

#endif