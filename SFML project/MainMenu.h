#include <SFML/Graphics.hpp>
#include "MenuStructure.h"
#include "TGUIEventHandler.h"
#include <SFML/System.hpp>
#include <TGUI/TGUI.hpp>
#pragma once
namespace GameMenus {
	auto mainMenu_Theme = tgui::Theme::create("../TGUI-0.7/widgets/Black.txt");
	MenuStructure mainMenu;
	MenuStructure MainMenu(int gameWidth, int gameHeight) {
		mainMenu.drawings_sfml.clear();
		mainMenu.drawings_tgui.clear();

		sf::Font *pokerFont = new sf::Font();
		sf::Texture *profilePicture = new sf::Texture();
		if(!profilePicture->loadFromFile("resources/"))

		if (!pokerFont->loadFromFile("resources/Electrolize-Regular.ttf")) {
			printf("Error loading font.");
		}
		/*
		sf::Text *testText = new sf::Text();
		testText->setFont(*pokerFont);
		testText->setString("This is a test string.");
		testText->setCharacterSize(72);
		testText->setFillColor(sf::Color(255, 0, 0));
		testText->setPosition(0, 0);
		*/
		sf::RectangleShape *playerRectangle = new sf::RectangleShape();
		playerRectangle->setFillColor(sf::Color(0, 18, 109, 255*0.6));
		playerRectangle->setSize(sf::Vector2f(gameWidth*0.25, gameHeight*0.2));
		playerRectangle->setPosition(gameWidth*0.02, gameHeight*0.02);

		sf::Sprite *profilePicture_graphic = new sf::Sprite();
		
		mainMenu.drawings_sfml.push_back(playerRectangle);
		return mainMenu;
	}
}