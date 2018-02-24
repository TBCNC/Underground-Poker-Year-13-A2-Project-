#include <SFML/Graphics.hpp>
#include "LoginMenu.h"
#include "MenuStructure.h"
#include "ScreenManagement.h"
#include "TGUIEvents.h"
#include "TGUIEventHandler.h"
#pragma once
namespace GameMenus {
	MenuStructure play_menu;
	MenuStructure PlayMenu(int gameWidth, int gameHeight) {
		play_menu.drawings_sfml.clear();
		play_menu.drawings_tgui.clear();

		sf::Font *pokerFont = new sf::Font();
		if (!pokerFont->loadFromFile("resources/Electrolize-Regular.ttf"))
			printf("Error loading font.");

		sf::RectangleShape* choiceRectangle = new sf::RectangleShape();
		choiceRectangle->setSize(sf::Vector2f(gameWidth*0.35, gameHeight*0.35));
		choiceRectangle->setPosition(sf::Vector2f((gameWidth / 2) - (choiceRectangle->getLocalBounds().width / 2), (gameHeight / 2) - (choiceRectangle->getLocalBounds().height / 2) - (gameHeight / 20)));
		choiceRectangle->setFillColor(sf::Color(103, 103, 103, 255 * 0.6));

		tgui::Button::Ptr findServerButton = theme->load("Button");
		findServerButton->setFont(*pokerFont);
		findServerButton->setText("Find a server");
		findServerButton->setSize(choiceRectangle->getLocalBounds().width*0.8, choiceRectangle->getLocalBounds().height*0.1);
		findServerButton->setPosition(choiceRectangle->getGlobalBounds().left + choiceRectangle->getLocalBounds().width / 2 - findServerButton->getSize().x / 2, choiceRectangle->getGlobalBounds().top + choiceRectangle->getLocalBounds().height*0.15);
		findServerButton->connect("pressed", [&]() {
			TGUIEvent *pressEvent = new TGUIEvent;
			pressEvent->menu = play_menu;
			pressEvent->eventType = TGUIEvents::CHANGE_TO_SERVER_LIST;
			TGUIEventHandler::events.push_back(pressEvent);
		});

		tgui::Button::Ptr createServerButton = theme->load("Button");
		createServerButton->setFont(*pokerFont);
		createServerButton->setText("Create a server");
		createServerButton->setSize(choiceRectangle->getLocalBounds().width*0.8, choiceRectangle->getLocalBounds().height*0.11);
		createServerButton->setPosition(choiceRectangle->getGlobalBounds().left + choiceRectangle->getLocalBounds().width / 2 - findServerButton->getSize().x / 2, choiceRectangle->getGlobalBounds().top + choiceRectangle->getLocalBounds().height*0.35);
		createServerButton->connect("pressed", [&]() {
			TGUIEvent *pressEvent = new TGUIEvent;
			pressEvent->eventType = TGUIEvents::CHANGE_TO_SERVER_SETUP;
			pressEvent->menu = play_menu;
			TGUIEventHandler::events.push_back(pressEvent);
		});

		tgui::Button::Ptr findCompButton = theme->load("Button");
		findCompButton->setFont(*pokerFont);
		findCompButton->setText("Play competitive");
		findCompButton->setSize(choiceRectangle->getLocalBounds().width*0.8, choiceRectangle->getLocalBounds().height*0.1);
		findCompButton->setPosition(choiceRectangle->getGlobalBounds().left + choiceRectangle->getLocalBounds().width / 2 - findServerButton->getSize().x / 2, choiceRectangle->getGlobalBounds().top + choiceRectangle->getLocalBounds().height*0.55);

		tgui::Button::Ptr backButton = theme->load("Button");
		backButton->setFont(*pokerFont);
		backButton->setText("Back to main menu");
		backButton->setSize(choiceRectangle->getLocalBounds().width*0.8, choiceRectangle->getLocalBounds().height*0.1);
		backButton->setPosition(choiceRectangle->getGlobalBounds().left + choiceRectangle->getLocalBounds().width / 2 - findServerButton->getSize().x / 2, choiceRectangle->getGlobalBounds().top + choiceRectangle->getLocalBounds().height*0.75);
		backButton->connect("pressed", [&]() {
			TGUIEvent *pressEvent = new TGUIEvent;
			pressEvent->eventType = TGUIEvents::CHANGE_TO_MAIN_MENU;
			pressEvent->menu = play_menu;
			TGUIEventHandler::events.push_back(pressEvent);
		});

		play_menu.drawings_sfml.push_back(choiceRectangle);
		play_menu.drawings_tgui.push_back(findServerButton);
		play_menu.drawings_tgui.push_back(createServerButton);
		play_menu.drawings_tgui.push_back(findCompButton);
		play_menu.drawings_tgui.push_back(backButton);
		return play_menu;
	}
};