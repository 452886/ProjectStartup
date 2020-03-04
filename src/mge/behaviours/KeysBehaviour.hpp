#ifndef KEYSBEHAVIOUR_HPP
#define KEYSBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include <map>
#include <string>

/**
 * KeysBehaviour allows you to move an object using the keyboard in its own local space.
 * Left right turns, forward back moves.
 */
class KeysBehaviour : public AbstractBehaviour
{
	public:
	    //move speed is in units per second, turnspeed in degrees per second
		KeysBehaviour(float pMoveSpeed = 5.0f, float pTurnSpeed = 45.0f, float tileSize = 10.0f);
        bool keyDown(char key);
		virtual ~KeysBehaviour();
		virtual void update( float pStep );

    private:
        float _moveSpeed;
        float _turnSpeed;
        float tileSize;
        void updatePressedKeys();

        std::map<char, bool> pressedKeys;
};

#endif // KEYSBEHAVIOUR_HPP
