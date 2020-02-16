#ifndef WORLD_HPP
#define WORLD_HPP

#include "mge/core/GameObject.hpp"
#include "mge/core/Light.hpp"

class Camera;
class Light;

class World : public GameObject
{
	public:
        World();

		void setMainCamera (Camera* pCamera);
		Camera* getMainCamera();

        //only used internally, do not use from outside
        void registerLight (Light* pLight);
        void unregisterLight (Light* pLight);

        Light* getLightAt (int pIndex);
        int getLightCount();


		// THIS IS ONLY USED FOR GIVING THE FRAGMENT SHADER THE RIGHT ARRAY INDEX AMMOUNT
		// YOU CAN'T USE THESE TO THE THE INDEX OF THAT SPECIFIC LIGHT
		// TO DO 
		int getLightTypeCount(LightType type);

		float ElapsedTime();

	private:
	    Camera* _mainCamera;
	    std::vector<Light*> _lights;

        World(const World&);
        World& operator=(const World&);
		
		sf::Clock _clock;

		int _pointLightCount = 0;
		int _spotLightCount = 0;
		int _dirLightCount = 0;
		int _ambientLightCount = 0;

};


#endif // WORLD_HPP
