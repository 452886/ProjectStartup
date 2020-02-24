#include <iostream>
#include <fstream>
#include <sstream>
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
#include "mge/Scenes/UnityImportScene.hpp"

#include "mge/materials/MaterialLib.hpp"


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

//build the game _world
void UnityImportScene::_initializeScene()
{
    Mesh* cubeMeshF = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
	

	TextureMaterial* box = MaterialLib::boxMat;

    cube = new GameObject("cube", glm::vec3(0, 0, 0));
    cube->scale(glm::vec3(5, 5, 5));
    cube->setMesh(cubeMeshF);
    cube->setMaterial(box);
    cube->setBehaviour(new KeysBehaviour(40));
    _world->add(cube);
    
    //SCENE SETUP

    //add camera first (it will be updated last)
    camera = new Camera("camera", glm::vec3(0, 0, 0));
    //camera->rotate(glm::radians(-20.0f), glm::vec3(1, 0, 0));
    _world->add(camera);
    _world->setMainCamera(camera);
    
    offSet = cube->getLocalPosition() - camera->getLocalPosition();

    //Default template is char
    //rapidxml::file<> xmlFile("mge/scene_export_default.xml");
    //rapidxml::file<> xmlFile("mge/scene_export_flipped.xml");
    //rapidxml::file<> xmlFile("mge/scene_export_rotated_wrong.xml");
    rapidxml::file<> xmlFile("mge/levels/withmaterials_export.xml");
    rapidxml::xml_document<> doc;
    //0 means default flags, parse the cr.p out of it
    doc.parse<0>(xmlFile.data());

    // Find our root node and send it off for further processing
    rapidxml::xml_node<>* root_node = doc.first_node("root");
    _processChildren(root_node, _world);

    AbstractMaterial* boxMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "testbox.png"), Texture::load(config::MGE_TEXTURE_PATH + "testboxspecular.png"));

    LightProperties properties;
    properties.ambient = glm::vec3(0.5f, 0.5f, 0.5f);
    properties.direction = glm::vec3(0.5f, 1, 0);

    Light* light = new Light("point first light", glm::vec3(0, 4.5f, 0), LightType::DIRECTION, properties);
    light->scale(glm::vec3(0.1f, 0.1f, 0.1f));
    light->setBehaviour(new KeysBehaviour(25));
    _world->add(light);
}



void UnityImportScene::_render() {

    camera->setLocalPosition(cube->getLocalPosition() + offSet);


    AbstractGame::_render();
    _updateHud();
}

void UnityImportScene::_updateHud() {
    std::string debugInfo = "";
    debugInfo += std::string("FPS:") + std::to_string((int)_fps) + "\n";

    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}

void UnityImportScene::_processChildren(rapidxml::xml_node<>* pXmlNode, GameObject* pGameObjectNode)
{
    for (rapidxml::xml_node<>* child = pXmlNode->first_node(); child != NULL; child = child->next_sibling())
    {
        _processSingle(child, pGameObjectNode);
    }
}

void UnityImportScene::_processSingle(rapidxml::xml_node<>* pXmlNode, GameObject* pGameObjectNode)
{
    GameObject* currentNode = pGameObjectNode;
    std::cout << "Processing " << pXmlNode->name() << std::endl;

    if (strcmp(pXmlNode->name(), "GameObject") == 0) {
        GameObject* newNode = _convertGameObject(pXmlNode, currentNode);
        currentNode->add(newNode);
        std::cout << newNode->getName() << " added to " << currentNode->getName() << std::endl;
        currentNode = newNode;
    }

    _processChildren(pXmlNode, currentNode);
}

GameObject* UnityImportScene::_convertGameObject(rapidxml::xml_node<>* pXmlNode, GameObject* pGameObjectNode)
{
    GameObject* gameObject = new GameObject("temp");
    //optimize this, use a materiallibrary!!
    AbstractMaterial* boxMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "chair_diffuse.png"), Texture::load(config::MGE_TEXTURE_PATH + "chair_specular.png"));
    gameObject->setMaterial(boxMaterial);
    gameObject->setBehaviour(new RotatingBehaviour());

    for (rapidxml::xml_attribute<>* attrib = pXmlNode->first_attribute();
        attrib != NULL;
        attrib = attrib->next_attribute()
        )
    {
        std::cout << attrib->name() << "=" << attrib->value() << std::endl;
        std::string attribName = attrib->name();

        //process code...
        if (attribName == "name") {

            gameObject->setName(attrib->value());

        }
        else if (attribName == "position") {

            glm::vec3 position;
            sscanf(attrib->value(), "(%f, %f, %f)", &position.x, &position.y, &position.z);
            gameObject->setLocalPosition(position);

        }
        else if (attribName == "rotation") {

            glm::quat rotation;
            sscanf(attrib->value(), "(%f, %f, %f, %f)", &rotation.x, &rotation.y, &rotation.z, &rotation.w);
            gameObject->rotate(glm::angle(rotation), glm::axis(rotation));
        }

        else if (attribName == "scale") {
            glm::vec3 scale;
            sscanf(attrib->value(), "(%f, %f, %f)", &scale.x, &scale.y, &scale.z);
            gameObject->scale(scale);
        }
        else if (attribName == "mesh") {
            Mesh* mesh = Mesh::load(config::MGE_MODEL_PATH + attrib->value());
            gameObject->setMesh(mesh);
        }
		else if (attribName == "material") {
			// Material libary


		}
    }

    return gameObject;
}


UnityImportScene::~UnityImportScene()
{
    //dtor
}
