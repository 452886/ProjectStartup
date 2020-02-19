#include <iostream>
#include <string>

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
#include "mge/Scenes/LightingExample.hpp"

//construct the game class into _window, _renderer and hud (other parts are initialized by build)
LightingExample::LightingExample() :AbstractGame(), _hud(0)
{
}

void LightingExample::initialize() {
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part so we can display some text
    std::cout << "Initializing HUD" << std::endl;
    _hud = new DebugHud(_window);
    std::cout << "HUD initialized." << std::endl << std::endl;
}

//build the game _world
void LightingExample::_initializeScene()
{
    //MESHES

    //load a bunch of meshes we will be using throughout this demo
    //each mesh only has to be loaded once, but can be used multiple times:
    //F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
    Mesh* planeMeshDefault = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
    Mesh* cubeMeshF = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
    Mesh* sphereMeshS = Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth.obj");

    //MATERIALS

    //create some materials to display the cube, the plane and the light
    AbstractMaterial* lightMaterial = new ColorMaterial(glm::vec3(1, 1, 0));
    AbstractMaterial* runicStoneMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "testbox.png"), Texture::load(config::MGE_TEXTURE_PATH + "testboxspecular.png"));
    AbstractMaterial* landMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "land.jpg"), Texture::load(config::MGE_TEXTURE_PATH + "testboxspecular.png"));
    AbstractMaterial* redMaterial = new ColorMaterial(glm::vec3(1, 0, 0));
    AbstractMaterial* blueMaterial = new ColorMaterial(glm::vec3(0, 0, 1));

    //SCENE SETUP

   //add camera first (it will be updated last)
    Camera* camera = new Camera("camera", glm::vec3(0, 6, 7));
    camera->rotate(glm::radians(-40.0f), glm::vec3(1, 0, 0));
    _world->add(camera);
    _world->setMainCamera(camera);

    //add the floor
    GameObject* plane = new GameObject("plane", glm::vec3(0, 0, 0));
    plane->scale(glm::vec3(5, 5, 5));
    plane->setMesh(planeMeshDefault);
    plane->setMaterial(landMaterial);
    _world->add(plane);

    //add a spinning sphere
    GameObject* sphere = new GameObject("sphere", glm::vec3(0, 0, 0));
    sphere->scale(glm::vec3(2.5, 2.5, 2.5));
    sphere->setMesh(sphereMeshS);
    sphere->setMaterial(runicStoneMaterial);
    sphere->setBehaviour(new RotatingBehaviour());
    _world->add(sphere);

    GameObject* cube = new GameObject("cube", glm::vec3(1.5f, 4.5, 4));
    cube->scale(glm::vec3(0.3f, 0.3f, 0.3f));
    cube->setMesh(cubeMeshF);
    cube->setMaterial(runicStoneMaterial);
    _world->add(cube);

    GameObject* cube2 = new GameObject("cube2", glm::vec3(1.5f, 4.5, 5));
    cube2->scale(glm::vec3(0.3f, 0.3f, 0.3f));
    cube2->setMesh(cubeMeshF);
    cube2->setMaterial(runicStoneMaterial);
    _world->add(cube2);

    LightProperties properties;
    properties.ambient = glm::vec3(0.2f, 0.2f, 0.2f);

    Light* light = new Light("point first light", glm::vec3(0, 4.5f, 0), LightType::POINT, properties);
    light->scale(glm::vec3(0.1f, 0.1f, 0.1f));
    light->setMesh(cubeMeshF);
    light->setMaterial(lightMaterial);
    light->setBehaviour(new KeysBehaviour(25));
    _world->add(light);

    LightProperties propertiesThree;
    propertiesThree.direction = glm::vec3(0, -1, 0);
    propertiesThree.cutOff = glm::cos(glm::radians(12.5f));
    propertiesThree.outerCutOff = glm::cos(glm::radians(15.0f));

    Light* lightThree = new Light("Spot second light", glm::vec3(4, 3, 0), LightType::SPOT, propertiesThree);
    lightThree->scale(glm::vec3(0.1f, 0.1f, 0.1f));
    lightThree->setMesh(cubeMeshF);
    lightThree->setMaterial(lightMaterial);
    lightThree->setBehaviour(new KeysBehaviour(50));
    _world->add(lightThree);

}

void LightingExample::_render() {
    AbstractGame::_render();
    _updateHud();
}

void LightingExample::_updateHud() {
    std::string debugInfo = "";
    debugInfo += std::string("FPS:") + std::to_string((int)_fps) + "\n";

    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}

LightingExample::~LightingExample()
{
    //dtor
}
