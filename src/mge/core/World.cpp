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

    switch (pLight->Type())
    {
    case LightType::POINT:

        _pointLightCount++;
        break;

    case LightType::SPOT:
        _spotLightCount++;
        break;

    case LightType::DIRECTION:
        _dirLightCount++;
        break;

    case LightType::AMBIENT:
        _ambientLightCount++;
        break;

    default:
        break;
    }
}

void World::unregisterLight(Light* pLight) {
    std::cout << "Unregistering light " << pLight->getName() << std::endl;
    if (_lights.size() == 0) return;

    switch (pLight->Type())
    {
    case LightType::POINT:
        if (_pointLightCount > 0)
            _pointLightCount--;

        break;

    case LightType::SPOT:
        if (_spotLightCount > 0)
            _spotLightCount--;
        break;

    case LightType::DIRECTION:
        if (_dirLightCount > 0)
            _dirLightCount--;
        break;

    case LightType::AMBIENT:
        if (_ambientLightCount > 0)
            _ambientLightCount--;
        break;

    default:
        break;
    }

    _lights.erase(std::remove(_lights.begin(), _lights.end(), pLight), _lights.end());
}

Light* World::getLightAt(int pIndex) {
    return _lights[pIndex];
}

int World::getLightCount() {
    return _lights.size();
}

int World::getLightTypeCount(LightType type)
{
    switch (type)
    {
    case LightType::POINT:
        return _pointLightCount;

        break;

    case LightType::SPOT:
        return _spotLightCount;

        break;

    case LightType::DIRECTION:
        return _dirLightCount;

        break;

    case LightType::AMBIENT:
        return _ambientLightCount;

        break;

    default:
        break;
    }
}
