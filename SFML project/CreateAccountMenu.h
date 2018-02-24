#include <SFML/Graphics.hpp>
#include "LoginMenu.h"
#include "MenuStructure.h"
#include "TGUIEvents.h"
#include "TGUIEventHandler.h"
#include <TGUI/TGUI.hpp>
#pragma once

namespace GameMenus {
	MenuStructure createAccountMenu;
	tgui::EditBox::Ptr userAccount_name = theme->load("EditBox");
	tgui::EditBox::Ptr userAccount_password = theme->load("EditBox");
	tgui::EditBox::Ptr userAccount_email = theme->load("EditBox");
	MenuStructure CreateAccountMenu(int gameWidth, int gameHeight) {
		createAccountMenu.drawings_sfml.clear();
		createAccountMenu.drawings_tgui.clear();
		sf::Font *pokerFont = new sf::Font();
		if (!pokerFont->loadFromFile("resources/Electrolize-Regular.ttf")) {
			printf("Error loading font.");
		}

		sf::RectangleShape *setupBox = new sf::RectangleShape();
		setupBox->setSize(sf::Vector2f(gameWidth*0.9, gameWidth*0.5));
		setupBox->setFillColor(sf::Color(103, 103, 103, 255 * 0.6));
		setupBox->setPosition(gameWidth / 2 - setupBox->getLocalBounds().width / 2, gameHeight / 2 - setupBox->getLocalBounds().height / 2);

		sf::Text *headingText = new sf::Text();
		headingText->setFont(*pokerFont);
		headingText->setCharacterSize(2.5*0.000017*gameWidth*gameHeight);
		headingText->setFillColor(sf::Color::White);
		headingText->setString("Account Creation");
		headingText->setPosition(setupBox->getGlobalBounds().left + setupBox->getLocalBounds().width / 2 - headingText->getLocalBounds().width / 2
			, setupBox->getGlobalBounds().top + setupBox->getLocalBounds().height*0.05);

		userAccount_name->setFont(*pokerFont);
		userAccount_name->setPosition(setupBox->getGlobalBounds().left + setupBox->getLocalBounds().width*0.05, headingText->getLocalBounds().top + headingText->getLocalBounds().height + setupBox->getLocalBounds().height*0.2);
		userAccount_name->setSize(setupBox->getLocalBounds().width*0.9, setupBox->getLocalBounds().height*0.1);
		userAccount_name->setDefaultText("Username");

		userAccount_password->setFont(*pokerFont);
		userAccount_password->setPosition(userAccount_name->getPosition().x, userAccount_name->getPosition().y + userAccount_name->getSize().y + setupBox->getLocalBounds().height*0.1);
		userAccount_password->setSize(setupBox->getLocalBounds().width*0.9, setupBox->getLocalBounds().height*0.1);
		userAccount_password->setDefaultText("Password");
		userAccount_password->setPasswordCharacter('*');

		userAccount_email->setFont(*pokerFont);
		userAccount_email->setPosition(userAccount_password->getPosition().x, userAccount_password->getPosition().y + userAccount_password->getSize().y + setupBox->getLocalBounds().height*0.1);
		userAccount_email->setSize(setupBox->getLocalBounds().width*0.9, setupBox->getLocalBounds().height*0.1);
		userAccount_email->setDefaultText("Email");

		sf::Text *account_notice = new sf::Text();
		account_notice->setFont(*pokerFont);
		account_notice->setCharacterSize(1 * 0.000017*gameWidth*gameHeight);
		account_notice->setString("By joining, you agree to our ToC and our privacy policy.");
		account_notice->setPosition(userAccount_email->getPosition().x, userAccount_email->getPosition().y + userAccount_email->getSize().y + setupBox->getLocalBounds().height*0.05);
		
		//tgui::Button::Ptr server_create_button = theme->load("Button");
		tgui::Button::Ptr account_create_button = theme->load("Button");
		
		account_create_button->setFont(*pokerFont);
		account_create_button->setSize(setupBox->getLocalBounds().width*0.9, setupBox->getLocalBounds().height*0.1);
		account_create_button->setText("Create Account!");
		account_create_button->setPosition(account_notice->getGlobalBounds().left, account_notice->getGlobalBounds().top + account_notice->getLocalBounds().height + setupBox->getLocalBounds().height*0.05);
		account_create_button->connect("pressed", [&]() {
			TGUIEvent *event = new TGUIEvent;
			event->eventType = TGUIEvents::CREATE_ACCOUNT;
			event->arguments = { userAccount_name->getText(),userAccount_password->getText(),userAccount_email->getText() };
			event->menu = createAccountMenu;
			TGUIEventHandler::events.push_back(event);
		});

		createAccountMenu.drawings_sfml.push_back(setupBox);
		createAccountMenu.drawings_sfml.push_back(headingText);
		createAccountMenu.drawings_tgui.push_back(userAccount_name);
		createAccountMenu.drawings_tgui.push_back(userAccount_password);
		createAccountMenu.drawings_tgui.push_back(userAccount_email);
		createAccountMenu.drawings_sfml.push_back(account_notice);
		createAccountMenu.drawings_tgui.push_back(account_create_button);
		return createAccountMenu;
	}
}