#include <iostream>
#include <string>
#include <stdio.h>
#include "glm.hpp"

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/GameObject.hpp"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "mge/defaultScene.hpp"

//construct the game class into _window, _renderer and hud (other parts are initialized by build)
DefaultScene::DefaultScene():AbstractGame (),_hud(0)
{
}

void DefaultScene::initialize() {
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part so we can display some text
	std::cout << "Initializing HUD" << std::endl;
	_hud = new DebugHud(_window);
	std::cout << "HUD initialized." << std::endl << std::endl;
}

//build the game _world
void DefaultScene::_initializeScene()
{
    //MESHES

    //load a bunch of meshes we will be using throughout this demo
    //each mesh only has to be loaded once, but can be used multiple times:
    //F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
    Mesh* planeMeshDefault = Mesh::load (config::MGE_MODEL_PATH+"plane.obj");
    Mesh* cubeMeshF = Mesh::load (config::MGE_MODEL_PATH+"cube_flat.obj");
    Mesh* sphereMeshS = Mesh::load (config::MGE_MODEL_PATH+"sphere_smooth.obj");

    //MATERIALS

    //create some materials to display the cube, the plane and the light
    AbstractMaterial* lightMaterial = new ColorMaterial (glm::vec3(1,1,0));
    AbstractMaterial* runicStoneMaterial = new TextureMaterial (Texture::load (config::MGE_TEXTURE_PATH+"runicfloor.jpg"));

    //SCENE SETUP

   //add camernewa first (it will be updated last)
    camera = new Camera ("camera", glm::vec3(0,3,3));
    //camera->rotate(glm::radians(-40.0f), glm::vec3(1, 0, 0));
    _world->add(camera);
    _world->setMainCamera(camera);

    //add the floor
    GameObject* plane = new GameObject ("plane", glm::vec3(0,0,0));
    plane->scale(glm::vec3(10,10,10));
    plane->setMesh(planeMeshDefault);
    plane->setMaterial(runicStoneMaterial);
    _world->add(plane);

    //add a light. Note that the light does ABSOLUTELY ZIP! NADA ! NOTHING !
    //It's here as a place holder to get you started.
    //Note how the texture material is able to detect the number of lights in the scene
    //even though it doesn't implement any lighting yet!

    Light* light = new Light("light", glm::vec3(0,4,0));
    light->scale(glm::vec3(0.1f, 0.1f, 0.1f));
    light->setMesh(cubeMeshF);
    light->setMaterial(lightMaterial);
    light->setBehaviour(new KeysBehaviour(25));
    _world->add(light);
}

void DefaultScene::updateCamera() {
    sf::Vector2u screenSize = _window->getSize();
    sf::Vector2i rawMousePos = sf::Mouse::getPosition(*_window);

    sf::Vector2f mousePos = sf::Vector2f(rawMousePos.x / (float)_window->getSize().x, rawMousePos.y / (float)_window->getSize().y);
    mousePos.x = 1.0 - mousePos.x * 2.0f;
    mousePos.y = 1.0 - mousePos.y * 2.0f;
    printf("%f %f\n", mousePos.x, mousePos.y);

    if(fabs(mousePos.x) >= 0.3f) {
        camera->rotate(glm::radians(mousePos.x), glm::vec3(0, 1, 0));
    }
    if (fabs(mousePos.y) >= 0.3f) {
        camera->rotate(glm::radians(mousePos.y), glm::vec3(1, 0, 0));
    }
}

void DefaultScene::_render() {
    AbstractGame::_render();
    _updateHud();

    //camera->rotate(glm::radians(2.0f), glm::vec3(0, 1, 0));
    updateCamera();
}

void DefaultScene::_updateHud() {
    std::string debugInfo = "";
    debugInfo += std::string ("FPS:") + std::to_string((int)_fps)+"\n";

    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}

DefaultScene::~DefaultScene()
{
	//dtor
}
