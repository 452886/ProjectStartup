#include "mge/behaviours/BackgroundMusicBehaviour.hpp"
#include "mge/config.hpp"

#include <iostream>
#include <string>
#include <fstream>

BackgroundMusicBehaviour::BackgroundMusicBehaviour()
{
	if (!buffer.loadFromFile(config::MGE_SOUND_PATH +"testbackgroundmusic.ogg")) {
		std::cout << "###################### kut ###############" << std::endl;
	}
	sound.setBuffer(buffer);
	sound.setLoop(true);
	sound.play();

	std::cout << "###################### iets ###############" << std::endl;
}

BackgroundMusicBehaviour::~BackgroundMusicBehaviour()
{
}

void BackgroundMusicBehaviour::update(float pStep)
{
}
