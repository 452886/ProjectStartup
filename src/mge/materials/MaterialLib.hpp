#ifndef MATERIALLIB_HPP
#define MATERIALLIB_HPP

#include "AbstractMaterial.hpp"
#include "TextureMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/util/HelperMethods.hpp"
#include <algorithm>

#include <string>
#include <iostream>
#include <fstream>
#include <istream>
#include <map>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

using namespace std;

class MaterialLib
{

public:
	MaterialLib();
	virtual ~MaterialLib();

	AbstractMaterial* getMaterial(std::string);

private:
	std::map<std::string, AbstractMaterial*> materials;
	void InitializeMaterials();

};


#endif // MATERIALLIB_HPPZ