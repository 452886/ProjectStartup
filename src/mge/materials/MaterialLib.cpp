#include "mge/materials/MaterialLib.hpp"
#include "mge/config.hpp"

TextureMaterial const MaterialLib::boxMat = TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"), Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"));
