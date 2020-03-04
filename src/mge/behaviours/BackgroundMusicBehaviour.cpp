#include "mge/behaviours/BackgroundMusicBehaviour.hpp"
#include "mge/config.hpp"

#include <iostream>
#include <string>
#include <fstream>

BackgroundMusicBehaviour::BackgroundMusicBehaviour()
{
	if (!buffer.loadFromFile(config::MGE_SOUND_PATH +"BaseMusicLoop.ogg")) {

	}
	if (!buffer2.loadFromFile(config::MGE_SOUND_PATH + "BeatMusicLoop.ogg")) {

	}
	if (!buffer3.loadFromFile(config::MGE_SOUND_PATH + "MysteryMusicLoop.ogg")) {

	}

	sound.setBuffer(buffer);
	sound.setLoop(false);
	sound.play();
}

BackgroundMusicBehaviour::~BackgroundMusicBehaviour()
{
}

void BackgroundMusicBehaviour::update(float pStep)
{

}
