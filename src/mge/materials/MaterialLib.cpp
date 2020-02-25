#include "mge/materials/MaterialLib.hpp"
#include "mge/config.hpp"


MaterialLib::MaterialLib()
{
	InitializeMaterials();
}

MaterialLib::~MaterialLib()
{

}

AbstractMaterial* MaterialLib::getMaterial(std::string matName)
{
	return materials[matName];
}

std::vector<std::string> split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

void MaterialLib::InitializeMaterials()
{
	for (const auto& entry : fs::directory_iterator(config::MGE_TEXTURE_PATH_DIFFUSE))
	{
		std::string filePath = entry.path().u8string();
		std::replace(filePath.begin(), filePath.end(), '\\', '/');
		std::vector<std::string> paths = split(filePath,'/');
		std::vector<std::string> nameAndExtension = split(paths.back(),'.');

		ifstream ifile;
		ifile.open(config::MGE_TEXTURE_PATH_SPECULAR + nameAndExtension[0] + "-specular.png");
		if (ifile) {
			AbstractMaterial* material = new TextureMaterial(Texture::load(filePath), Texture::load(config::MGE_TEXTURE_PATH_SPECULAR + nameAndExtension[0] + "-specular.png"));
			materials[nameAndExtension[0]] = material;
		}
		else {
			AbstractMaterial* material = new TextureMaterial(Texture::load(filePath), Texture::load(config::MGE_TEXTURE_PATH_SPECULAR + "no-specular.png"));
			materials[nameAndExtension[0]] = material;
		}
		ifile.close();
	}	
}



