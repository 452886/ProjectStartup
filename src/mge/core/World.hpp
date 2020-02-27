#ifndef WORLD_HPP
#define WORLD_HPP

#include "mge/core/GameObject.hpp"
#include "mge/core/Light.hpp"
#include "mge/lights/DirLight.hpp"
#include "mge/lights/SpotLight.hpp"
#include "mge/lights/PointLight.hpp"
#include "mge/materials/MaterialLib.hpp"

class Camera;
class Light;

class World : public GameObject
{
public:
	World();

	void setMainCamera(Camera* pCamera);
	Camera* getMainCamera();

	//only used internally, do not use from outside
	void registerLight(Light* pLight);
	void unregisterLight(Light* pLight);

	Light* getLightAt(int pIndex);
	int getTotalLightCount();

	int getLightTypeCount(LightType type);

	MaterialLib* matLib = new MaterialLib();

private:
	Camera* _mainCamera;
	std::vector<Light*> _lights;

	int _dirLightCount = 0;
	int _pointLightCount = 0;
	int _spotLightCount = 0;

	World(const World&);
	World& operator=(const World&);
};


#endif // WORLD_HPP
