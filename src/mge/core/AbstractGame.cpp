#include <iostream>

#include "AbstractGame.hpp"
#include "mge/core/Renderer.hpp"
#include "mge/core/World.hpp"
#include "mge/config.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"

AbstractGame::AbstractGame():_window(NULL),_renderer(NULL),_world(NULL), _fps(0)
{
    //ctor
}

AbstractGame::~AbstractGame()
{
    //dtor
    delete _window;
    delete _renderer;
    delete _world;
}

void AbstractGame::initialize() {
    std::cout << "Initializing engine..." << std::endl << std::endl;
    _initializeWindow();
    _printVersionInfo();
    _initializeGlew();
    _initializeRenderer();
    _initializeWorld();
    _initializeScene();
    std::cout << std::endl << "Engine initialized." << std::endl << std::endl;
}

///SETUP

void AbstractGame::_initializeWindow() {
	std::cout << "Initializing window..." << std::endl;
	_window = new sf::RenderWindow( sf::VideoMode(1920,1080), "My Game!", sf::Style::Default, sf::ContextSettings(24,8,0,3,3));
	//_window->setVerticalSyncEnabled(true);
    std::cout << "Window initialized." << std::endl << std::endl;

}

void AbstractGame::_printVersionInfo() {
	std::cout << "Context info:" << std::endl;
    std::cout << "----------------------------------" << std::endl;
    //print some debug stats for whoever cares
    const GLubyte *vendor = glGetString( GL_VENDOR );
    const GLubyte *renderer = glGetString( GL_RENDERER );
    const GLubyte *version = glGetString( GL_VERSION );
    const GLubyte *glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );
    //nice consistency here in the way OpenGl retrieves values
    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    printf("GL Vendor : %s\n", vendor);
    printf("GL Renderer : %s\n", renderer);
    printf("GL Version (string) : %s\n", version);
    printf("GL Version (integer) : %d.%d\n", major, minor);
    printf("GLSL Version : %s\n", glslVersion);

    std::cout << "----------------------------------" << std::endl << std::endl;
}

void AbstractGame::_initializeGlew() {
	std::cout << "Initializing GLEW..." << std::endl;
    //initialize the opengl extension wrangler
    GLint glewStatus = glewInit();
	std::cout << "Initialized GLEW, status (1 == OK, 0 == FAILED):" << (glewStatus == GLEW_OK) << std::endl << std::endl;
}

void AbstractGame::_initializeRenderer() {
    //setup our own renderer
	std::cout << "Initializing renderer..." << std::endl;
	_renderer = new Renderer();
    _renderer->setClearColor(0,0,0);
    std::cout << "Renderer done." << std::endl << std::endl;
}

void AbstractGame::_initializeWorld() {
    //setup the world
	std::cout << "Initializing world..." << std::endl;
	_world = new World();
    std::cout << "World initialized." << std::endl << std::endl;
}

///MAIN GAME LOOP

void AbstractGame::run()
{
    //setting to calculate fps
	sf::Clock renderClock;
    int frameCount = 0;
    float timeSinceLastFPSCalculation = 0;

	//settings to make sure the update loop runs at 60 fps
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Clock updateClock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (_window->isOpen()) {
		timeSinceLastUpdate += updateClock.restart();

		if (timeSinceLastUpdate > timePerFrame)
		{
            glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		    while (timeSinceLastUpdate > timePerFrame) {
                timeSinceLastUpdate -= timePerFrame;
                _update(timePerFrame.asSeconds());
		    }

            _render();
            _window->display();

            //fps count is updated once every 1 second
            frameCount++;
            timeSinceLastFPSCalculation += renderClock.restart().asSeconds();
            if (timeSinceLastFPSCalculation > 1) {
                _fps = frameCount/timeSinceLastFPSCalculation;
                timeSinceLastFPSCalculation -= 1;
                frameCount = 0;
            }

		}

		//empty the event queue
		_processEvents();
    }
}

void AbstractGame::_update(float pStep) {
    _world->update(pStep);
}

void AbstractGame::_render () {
    _renderer->render(_world);
}

void AbstractGame::_processEvents()
{
	sf::Event event;
	bool exit = false;

	//we must empty the event queue
	while( _window->pollEvent( event ) ) {
        //give all system event listeners a chance to handle events
        //optionally to be implemented by you for example you could implement a
        //SystemEventDispatcher / SystemEventListener pair which allows Listeners to
        //register with the dispatcher and then do something like:
        //SystemEventDispatcher::dispatchEvent(event);

        switch (event.type) {
            case sf::Event::Closed:
                exit = true;
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    exit = true;
                }
                break;
            case sf::Event::Resized:
                //would be better to move this to the renderer
                //this version implements nonconstrained match viewport scaling
                glViewport(0, 0, event.size.width, event.size.height);
                break;

            default:
                break;
        }
	}

	if (exit) {
        _window->close();
	}
}

void AbstractGame::_processChildren(rapidxml::xml_node<>* pXmlNode, GameObject* pGameObjectNode)
{
	for (rapidxml::xml_node<>* child = pXmlNode->first_node(); child != NULL; child = child->next_sibling())
	{
		_processSingle(child, pGameObjectNode);
	}
}

void AbstractGame::_processSingle(rapidxml::xml_node<>* pXmlNode, GameObject* pGameObjectNode)
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

GameObject* AbstractGame::_convertGameObject(rapidxml::xml_node<>* pXmlNode, GameObject* pGameObjectNode)
{
	GameObject* gameObject = new GameObject("temp");

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
			std::cout << attrib->value() << std::endl;
			gameObject->setMaterial(_world->matLib->getMaterial(attrib->value()));
		}
		else if (attribName == "behaviours") {
			// Set the behaviour
			std::string upperCase = attrib->value();
			std::transform(upperCase.begin(), upperCase.end(), upperCase.begin(), ::toupper);

			std::vector<std::string> behaviours = HelperMethods::split(upperCase, '-');

			for (auto const& value : behaviours) {
				AddBehaviourFromString(gameObject, value);
			}


		}
	}

	return gameObject;
}

void AbstractGame::AddBehaviourFromString(GameObject* gameObject, std::string n) {
	// Imagine not being able to build a switch statment on strings

	if (n == "ROTATECLOCKWISE")
		gameObject->setBehaviour(new RotatingBehaviour());
	else if (n == "ROTATECOUNTERCLOCKWISE")
		gameObject->setBehaviour(new RotatingBehaviour());
	else if (n == "KEYMOVEMEND")
		gameObject->setBehaviour(new KeysBehaviour(5));

}

