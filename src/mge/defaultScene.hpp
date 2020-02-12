#ifndef DEFAULTSCENE_HPP
#define DEFAULTSCENE_HPP

#include "mge/core/AbstractGame.hpp"
#include <mge\core\Camera.hpp>

class DebugHud;

/**
 * An example subclass of AbstractGame showing how we can setup a scene.
 */
class DefaultScene: public AbstractGame
{
    //PUBLIC FUNCTIONS

	public:
		DefaultScene();
		virtual ~DefaultScene();

        //override initialize so we can add a DebugHud
        virtual void initialize();

	protected:
	    //override so we can construct the actual scene
        virtual void _initializeScene();

	    //override render to render the hud as well.
	    virtual void _render();

	private:
		DebugHud* _hud;                   //hud display
		float fov = 70.0f;
		Camera* camera;
        void _updateHud();
		void updateCamera();

		DefaultScene(const DefaultScene&);
		DefaultScene& operator=(const DefaultScene&);
};

#endif // DEFAULTSCENE_HPP
