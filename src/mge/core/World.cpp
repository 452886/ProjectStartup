#include <iostream>
#include <algorithm>

#include "mge/core/World.hpp"

World::World() :GameObject("root"), _mainCamera(0)
{
    _world = this;
}

void World::setMainCamera(Camera* pCamera) {
    if (pCamera != NULL) _mainCamera = pCamera;
}

Camera* World::getMainCamera() {
    return _mainCamera;
}

void World::registerLight(Light* pLight) {
    std::cout << "Registering light " << pLight->getName() << std::endl;
    _lights.push_back(pLight);

    switch (pLight->GetType())
    {
    case LightType::POINT:
		_pointLights.push_back(dynamic_cast<PointLight*>(pLight));
        break;

    case LightType::SPOT:
		_spotLights.push_back(dynamic_cast<SpotLight*>(pLight));
        break;

    case LightType::DIRECTION:
		_dirLights.push_back(dynamic_cast<DirLight*>(pLight));
        break;

    case LightType::AMBIENT:
		// to be implemented
        break;

    default:
        break;
    }
}

void World::unregisterLight(Light* pLight) {
    std::cout << "Unregistering light " << pLight->getName() << std::endl;
    if (_lights.size() == 0) return;

    switch (pLight->GetType())
    {
    case LightType::POINT:
		_pointLights.erase(std::remove(_pointLights.begin(), _pointLights.end(), dynamic_cast<PointLight*>(pLight)), _pointLights.end());
        break;

    case LightType::SPOT:
		_spotLights.erase(std::remove(_spotLights.begin(), _spotLights.end(), dynamic_cast<SpotLight*>(pLight)), _spotLights.end());
        break;

    case LightType::DIRECTION:
		_dirLights.erase(std::remove(_dirLights.begin(), _dirLights.end(), dynamic_cast<DirLight*>(pLight)), _dirLights.end());
        break;

    case LightType::AMBIENT:
		// To be implemented
        break;

    default:
        break;
    }
    _lights.erase(std::remove(_lights.begin(), _lights.end(), pLight), _lights.end());
}

Light* World::getLightAt(int pIndex) {
    return _lights[pIndex];
}

int World::getTotalLightCount() {
    return _lights.size();
}

DirLight* World::getDirLightAt(int pIndex)
{
	return _dirLights[pIndex];
}

SpotLight* World::getSpotLightAt(int pIndex)
{
	return _spotLights[pIndex];
}

PointLight* World::getPointLightAt(int pIndex)
{
	return _pointLights[pIndex];
}

int World::getLightTypeCount(LightType type)
{
	switch (type)
	{
	case LightType::POINT:
		return _pointLights.size();
		break;

	case LightType::SPOT:
		return _spotLights.size();
		break;

	case LightType::DIRECTION:
		return _dirLights.size();
		break;

	case LightType::AMBIENT:
		return 0;
		break;

	default:
		break;
	}
	return 0;
}
