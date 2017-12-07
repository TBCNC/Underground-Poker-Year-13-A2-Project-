#include <SFML/Graphics.hpp>
#include "MenuStructure.h"
#pragma once
namespace GameMenus
{
	MenuStructure BackgroundImage(int gameWidth, int gameHeight)
	{
		MenuStructure background;
		sf::Texture *texture_background = new sf::Texture();
		if (!texture_background->loadFromFile("resources/background.png", sf::IntRect(0, 0, gameWidth, gameHeight))) {
			//Error
			printf("Could not open texture.");
		}
		texture_background->setSmooth(true);
		sf::Sprite *sprite_background = new sf::Sprite(*texture_background);
		background.drawings_sfml.push_back(sprite_background);
		return background;
	}
}