#include "mge/behaviours/BackgroundMusicBehaviour.hpp"
#include "mge/config.hpp"

#include <iostream>
#include <string>
#include <fstream>

BackgroundMusicBehaviour::BackgroundMusicBehaviour()
{
	if (!buffer.loadFromFile(config::MGE_SOUND_PATH +"BaseMusicLoop.ogg")) {

	}
	sound.setBuffer(buffer);
	sound.setLoop(true);
	sound.play();
}

BackgroundMusicBehaviour::~BackgroundMusicBehaviour()
{
}

void BackgroundMusicBehaviour::update(float pStep)
{
}
