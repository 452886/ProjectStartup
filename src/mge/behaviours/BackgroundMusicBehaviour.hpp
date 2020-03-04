#ifndef BACKGROUNDMUSICBEHAVIOUR_HPP
#define BACKGROUNDMUSICBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "SFML/Audio.hpp"
#include <iostream>

class BackgroundMusicBehaviour : public AbstractBehaviour
{
	public:	
		BackgroundMusicBehaviour();
		virtual ~BackgroundMusicBehaviour();
		virtual void update( float pStep );


	private:
		sf::SoundBuffer buffer;
		sf::SoundBuffer buffer2;
		sf::SoundBuffer buffer3;
		sf::Sound sound;
};

#endif // BACKGROUNDMUSICBEHAVIOUR_HPP
