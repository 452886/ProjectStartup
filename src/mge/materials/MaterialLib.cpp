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

void MaterialLib::InitializeMaterials()
{
	for (const auto& entry : fs::directory_iterator(config::MGE_TEXTURE_PATH_DIFFUSE))
	{
		std::string filePath = entry.path().u8string();
		std::replace(filePath.begin(), filePath.end(), '\\', '/');
		std::vector<std::string> paths = HelperMethods::split(filePath,'/');
		std::vector<std::string> nameAndExtension = HelperMethods::split(paths.back(),'.');

		ifstream ifileSpecular;
		ifileSpecular.open(config::MGE_TEXTURE_PATH_SPECULAR + nameAndExtension[0] + "-specular.png");
		ifstream ifileEmission;
		ifileEmission.open(config::MGE_TEXTURE_PATH_EMISSION + nameAndExtension[0] + "-emission.png");
		if (ifileSpecular) {
			if (ifileEmission) {
				AbstractMaterial* material = new TextureMaterial(Texture::load(filePath), Texture::load(config::MGE_TEXTURE_PATH_SPECULAR + nameAndExtension[0] + "-specular.png"), Texture::load(config::MGE_TEXTURE_PATH_EMISSION + nameAndExtension[0] + "-emission.png"));
				materials[nameAndExtension[0]] = material;
				std::cout << "Has specular and emission" << std::endl;
			}
			else {
				AbstractMaterial* material = new TextureMaterial(Texture::load(filePath), Texture::load(config::MGE_TEXTURE_PATH_SPECULAR + nameAndExtension[0] + "-specular.png"), Texture::load(config::MGE_TEXTURE_PATH_EMISSION + "no-emission.png"));
				materials[nameAndExtension[0]] = material;
				std::cout << "Has specular but no emission" << std::endl;
			}
		}
		else {
			if (ifileEmission) {
				AbstractMaterial* material = new TextureMaterial(Texture::load(filePath), Texture::load(config::MGE_TEXTURE_PATH_SPECULAR + "no-specular.png"), Texture::load(config::MGE_TEXTURE_PATH_EMISSION + nameAndExtension[0] + "-emission.png"));
				materials[nameAndExtension[0]] = material;
				std::cout << "Has no specular but does have emission" << std::endl;

			}
			else {
				AbstractMaterial* material = new TextureMaterial(Texture::load(filePath), Texture::load(config::MGE_TEXTURE_PATH_SPECULAR + "no-specular.png"), Texture::load(config::MGE_TEXTURE_PATH_EMISSION + "no-emission.png"));
				materials[nameAndExtension[0]] = material;
				std::cout << "Has no specular and no emission" << std::endl;

			}
		}
		ifileEmission.close();
		ifileSpecular.close();
	}	
}



