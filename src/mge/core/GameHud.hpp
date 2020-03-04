#ifndef GAMEHUD_HPP
#define GAMEHUD_HPP

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <iostream>


class GameHud {

	public :
		GameHud(sf::RenderWindow* aWindow);
		virtual ~GameHud();

		void draw();

	private:
		sf::RenderWindow* _window;
		sf::Sprite _daan;
		sf::Texture _daanTexture;

		sf::Font _font;
		sf::Text _text;


		GameHud(const GameHud&);
		GameHud& operator=(const GameHud&);
};

#endif