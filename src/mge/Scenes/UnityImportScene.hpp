#ifndef UNITYIMPORTSCENE_HPP
#define UNITYIMPORTSCENE_HPP

#include "mge/core/AbstractGame.hpp"

class DebugHud;
class GameObject;

/**
 * An example subclass of AbstractGame showing how we can setup a scene.
 */
class UnityImportScene : public AbstractGame
{
	//PUBLIC FUNCTIONS

public:
	UnityImportScene();
	virtual ~UnityImportScene();

	//override initialize so we can add a DebugHud
	virtual void initialize();

protected:
	//override so we can construct the actual scene
	virtual void _initializeScene();

	//override render to render the hud as well.
	virtual void _render();

private:
	DebugHud* _hud;                   //hud display
	GameHud* _gameHud;

	void _updateHud();

	UnityImportScene(const UnityImportScene&);
	UnityImportScene& operator=(const UnityImportScene&);

};

#endif // UNITYIMPORTSCENE_HPP
