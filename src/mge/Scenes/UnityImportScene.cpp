#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "glm.hpp"

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"
#include "mge/lights/PointLight.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/GameObject.hpp"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "mge/Scenes/UnityImportScene.hpp"

#include "mge/materials/MaterialLib.hpp"

#include "SFML/System/Clock.hpp"


//construct the game class into _window, _renderer and hud (other parts are initialized by build)
UnityImportScene::UnityImportScene() :AbstractGame(), _hud(0)
{
}

void UnityImportScene::initialize() {
	//setup the core part
	AbstractGame::initialize();

	//setup the custom part so we can display some text
	std::cout << "Initializing HUD" << std::endl;
	_hud = new DebugHud(_window);
	std::cout << "HUD initialized." << std::endl << std::endl;
}


GameObject* cube;
Camera* camera;
glm::vec3 offSet;

sf::Clock _clock;
int framespast;

//build the game _world
void UnityImportScene::_initializeScene()
{
	Mesh* cubeMeshF = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
	AbstractMaterial* boxmaterial = _world->matLib->getMaterial("box");

	//SCENE SETUP

	//Default template is char
	rapidxml::file<> xmlFile("mge/levels/obstaclePainter_export.xml");
	rapidxml::xml_document<> doc;
	//0 means default flags, parse the cr.p out of it
	doc.parse<0>(xmlFile.data());

	// Find our root node and send it off for further processing
	rapidxml::xml_node<>* root_node = doc.first_node("root");

	_processLevelData(root_node, _world);
}

void UnityImportScene::_render() {
	AbstractGame::_render();
	_updateHud();
}

void UnityImportScene::_updateHud() {
	std::string debugInfo = "";
	debugInfo += std::string("FPS:") + std::to_string((int)_fps) + "\n";

	_hud->setDebugInfo(debugInfo);
	_hud->draw();
}


UnityImportScene::~UnityImportScene()
{
	//dtor
}
