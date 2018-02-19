#include <SFML/Graphics.hpp>
#include "MenuStructure.h"
#include "TGUIEvents.h"
#include "TGUIEventHandler.h"
#pragma once

namespace GameMenus {
	MenuStructure serverMenu;
	MenuStructure ServerSetup(int gameWidth, int gameHeight) {
		serverMenu.drawings_sfml.clear();
		serverMenu.drawings_tgui.clear();
		sf::Font *pokerFont = new sf::Font();
		if (!pokerFont->loadFromFile("resources/Electrolize-Regular.ttf")) {
			printf("Error loading font.");
		}

		sf::RectangleShape *setupBox = new sf::RectangleShape();
		setupBox->setSize(sf::Vector2f(gameWidth*0.9, gameWidth*0.5));
		setupBox->setFillColor(sf::Color(103, 103, 103, 255 * 0.6));
		setupBox->setPosition(gameWidth / 2 - setupBox->getLocalBounds().width / 2, gameHeight / 2 - setupBox->getLocalBounds().height/2);
		serverMenu.drawings_sfml.push_back(setupBox);
		return serverMenu;
	}
}