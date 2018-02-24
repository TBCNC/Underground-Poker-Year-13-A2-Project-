#include <SFML/Graphics.hpp>
#include "MenuStructure.h"
#include "TGUIEvents.h"
#include "TGUIEventHandler.h"
#pragma once

namespace GameMenus {
	MenuStructure serverMenu;

	tgui::EditBox::Ptr server_name = theme->load("EditBox");
	tgui::EditBox::Ptr server_password = theme->load("EditBox");
	tgui::EditBox::Ptr server_port = theme->load("EditBox");
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
		
		sf::Text *headingText = new sf::Text();
		headingText->setFont(*pokerFont);
		headingText->setCharacterSize(2.5*0.000017*gameWidth*gameHeight);
		headingText->setFillColor(sf::Color::White);
		headingText->setString("Server Options");
		headingText->setPosition(setupBox->getGlobalBounds().left + setupBox->getLocalBounds().width / 2 - headingText->getLocalBounds().width / 2
			, setupBox->getGlobalBounds().top + setupBox->getLocalBounds().height*0.05);

		server_name->setFont(*pokerFont);
		server_name->setPosition(setupBox->getGlobalBounds().left+setupBox->getLocalBounds().width*0.05, headingText->getLocalBounds().top + headingText->getLocalBounds().height + setupBox->getLocalBounds().height*0.2);
		server_name->setSize(setupBox->getLocalBounds().width*0.9, setupBox->getLocalBounds().height*0.1);
		server_name->setDefaultText("Server title");
		
		server_password->setFont(*pokerFont);
		server_password->setPosition(server_name->getPosition().x, server_name->getPosition().y+server_name->getSize().y+setupBox->getLocalBounds().height*0.1);
		server_password->setSize(setupBox->getLocalBounds().width*0.9, setupBox->getLocalBounds().height*0.1);
		server_password->setDefaultText("Password (leave blank if none)");
		server_password->setPasswordCharacter('*');

		server_port->setFont(*pokerFont);
		server_port->setPosition(server_password->getPosition().x, server_password->getPosition().y + server_password->getSize().y + setupBox->getLocalBounds().height*0.1);
		server_port->setSize(setupBox->getLocalBounds().width*0.9, setupBox->getLocalBounds().height*0.1);
		server_port->setDefaultText("Port Number");

		sf::Text *server_port_notice = new sf::Text();
		server_port_notice->setFont(*pokerFont);
		server_port_notice->setCharacterSize(1 * 0.000017*gameWidth*gameHeight);
		server_port_notice->setString("Make sure this port number is forwarded otherwise nobody will be able to join!");
		server_port_notice->setPosition(server_port->getPosition().x, server_port->getPosition().y + server_port->getSize().y + setupBox->getLocalBounds().height*0.05);

		tgui::Button::Ptr server_create_button = theme->load("Button");
		server_create_button->setFont(*pokerFont);
		server_create_button->setSize(setupBox->getLocalBounds().width*0.9, setupBox->getLocalBounds().height*0.1);
		server_create_button->setText("Create server!");
		server_create_button->setPosition(server_port_notice->getGlobalBounds().left, server_port_notice->getGlobalBounds().top + server_port_notice->getLocalBounds().height + setupBox->getLocalBounds().height*0.05);
		server_create_button->connect("pressed", [&]() {
			TGUIEvent *event = new TGUIEvent;
			event->eventType = TGUIEvents::CREATE_SERVER;
			event->arguments = {server_name->getText(),server_password->getText(),server_port->getText()};
			event->menu = serverMenu;
			TGUIEventHandler::events.push_back(event);
		});

		serverMenu.drawings_sfml.push_back(setupBox);
		serverMenu.drawings_sfml.push_back(headingText);
		serverMenu.drawings_tgui.push_back(server_name);
		serverMenu.drawings_tgui.push_back(server_password);
		serverMenu.drawings_tgui.push_back(server_port);
		serverMenu.drawings_sfml.push_back(server_port_notice);
		serverMenu.drawings_tgui.push_back(server_create_button);
		return serverMenu;
	}
}