#ifndef UNITYIMPORTSCENE_HPP
#define UNITYIMPORTSCENE_HPP

#include "mge/core/AbstractGame.hpp"

#include <rapidxml-1.13/rapidxml.hpp>
#include "rapidxml-1.13/rapidxml_utils.hpp"

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

	void _updateHud();


	void _processChildren(rapidxml::xml_node<>* pXmlNode, GameObject* pGameObjectNode);
	void _processSingle(rapidxml::xml_node<>* pXmlNode, GameObject* pGameObjectNode);
	GameObject* _convertGameObject(rapidxml::xml_node<>* pXmlNode, GameObject* pGameObjectNode);


	UnityImportScene(const UnityImportScene&);
	UnityImportScene& operator=(const UnityImportScene&);

};

#endif // UNITYIMPORTSCENE_HPP
