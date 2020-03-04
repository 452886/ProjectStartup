#include "mge/core/GameHud.hpp"
#include "mge/config.hpp"

GameHud::GameHud(sf::RenderWindow* aWindow) : _window(aWindow)
{
	_daanTexture.loadFromFile(config::MGE_UI_SPRITE + "daan.jpg");
	_daan.setTexture(_daanTexture);

	if (!_font.loadFromFile(config::MGE_FONT_PATH + "arial.ttf")) {
		std::cout << "Could not load font, exiting..." << std::endl;
		return;
	}

	_daan.setScale(sf::Vector2(0.1f,0.1f));
	_daan.setPosition(sf::Vector2(100.0f, 700.0f));

	_text.setFont(_font);
	_text.setPosition(sf::Vector2(100.0f, 840.0f));
	_text.setString("Daans collected: ");
}

GameHud::~GameHud()
{
}

void GameHud::draw()
{
	glActiveTexture(GL_TEXTURE0);
	_window->pushGLStates();
	_window->draw(_daan);
	_window->draw(_text);
	_window->popGLStates();
}

