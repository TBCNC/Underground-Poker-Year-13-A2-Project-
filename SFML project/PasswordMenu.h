#include <SFML/Graphics.hpp>
#include "LoginMenu.h"
#include "MenuStructure.h"
#include "TGUIEvents.h"
#include "TGUIEventHandler.h"
#include <TGUI/TGUI.hpp>
#include "../Network/PasswordHash.h"
#pragma once

namespace GameMenus {
	MenuStructure passwordBox;
	std::string originalHash;
	tgui::EditBox::Ptr password_field = theme->load("EditBox");
	MenuStructure PasswordBox(int gameWidth, int gameHeight, std::string passwordHash) {
		originalHash = passwordHash;
		passwordBox.drawings_sfml.clear();
		passwordBox.drawings_tgui.clear();
		sf::Font *pokerFont = new sf::Font();
		if (!pokerFont->loadFromFile("resources/Electrolize-Regular.ttf")) {
			printf("Error loading font.");
		}
		
		sf::RectangleShape *mainBox = new sf::RectangleShape();
		mainBox->setSize(sf::Vector2f(gameWidth*0.3, gameHeight*0.3));
		mainBox->setFillColor(sf::Color(103, 103, 103, 255 * 0.6));
		mainBox->setPosition(gameWidth / 2 - mainBox->getLocalBounds().width / 2, gameHeight / 2 - mainBox->getLocalBounds().height / 2);

		sf::Text *headingText = new sf::Text();
		headingText->setFont(*pokerFont);
		headingText->setCharacterSize(1.5 * 0.000017*gameWidth*gameHeight);
		headingText->setString("This server requires a password");
		headingText->setPosition(mainBox->getGlobalBounds().left + mainBox->getLocalBounds().width / 2 - headingText->getLocalBounds().width / 2, mainBox->getGlobalBounds().top + mainBox->getLocalBounds().height*0.05);

		password_field->setFont(*pokerFont);
		password_field->setSize(mainBox->getLocalBounds().width*0.8, mainBox->getLocalBounds().height*0.2);
		password_field->setPosition(mainBox->getGlobalBounds().left + mainBox->getLocalBounds().width*0.1,headingText->getGlobalBounds().top+headingText->getLocalBounds().height+mainBox->getLocalBounds().height*0.1);
		password_field->setPasswordCharacter('*');
		password_field->setDefaultText("Password");

		tgui::Button::Ptr join_button = theme->load("Button");
		join_button->setFont(*pokerFont);
		join_button->setText("Join server");
		join_button->setSize(mainBox->getLocalBounds().width*0.8, mainBox->getLocalBounds().height*0.2);
		join_button->setPosition(mainBox->getGlobalBounds().left + mainBox->getLocalBounds().width*0.1, password_field->getPosition().y + password_field->getSize().y + mainBox->getLocalBounds().height*0.1);
		join_button->connect("pressed",[&]() {
			TGUIEvent *pressEvent = new TGUIEvent;
			if (PasswordHash::ComparePasswords(password_field->getText(), originalHash)) {
				pressEvent->arguments.push_back("1");
			}
			else {
				pressEvent->arguments.push_back("0");
			}
			pressEvent->menu = passwordBox;
			pressEvent->eventType = TGUIEvents::PASSWORD_ENTERED;
			TGUIEventHandler::events.push_back(pressEvent);
		});

		passwordBox.drawings_sfml.push_back(mainBox);
		passwordBox.drawings_sfml.push_back(headingText);
		passwordBox.drawings_tgui.push_back(password_field);
		passwordBox.drawings_tgui.push_back(join_button);
		return passwordBox;
	}
}