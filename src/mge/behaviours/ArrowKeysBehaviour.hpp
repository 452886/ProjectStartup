#ifndef ARROWKEYSBEHAVIOUR_HPP
#define ARROWKEYSBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"

/**
 * KeysBehaviour allows you to move an object using the keyboard in its own local space.
 * Left right turns, forward back moves.
 */
class ArrowKeysBehaviour : public AbstractBehaviour
{
public:
    //move speed is in units per second, turnspeed in degrees per second
    ArrowKeysBehaviour(float pMoveSpeed = 5, float pTurnSpeed = 45);
    virtual ~ArrowKeysBehaviour();
    virtual void update(float pStep);

private:
    float _moveSpeed;
    float _turnSpeed;
};

#endif // ARROWKEYSBEHAVIOUR_HPP
