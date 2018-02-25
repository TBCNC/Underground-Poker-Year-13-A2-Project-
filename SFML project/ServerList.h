#include <SFML/Graphics.hpp>
#include "MenuStructure.h"
#include "ScreenManagement.h"
#include "TGUIEvents.h"
#include "TGUIEventHandler.h"
#include "../Network/UserServers.h"
#include <vector>
#pragma once
namespace GameMenus {
	MenuStructure serverList;
	std::vector<UserServer> allServers;
	tgui::ListBox::Ptr serverListBox = theme->load("ListBox");
	MenuStructure ServerList(int gameWidth, int gameHeight) {
		serverList.drawings_sfml.clear();
		serverList.drawings_tgui.clear();

		sf::Font *pokerFont = new sf::Font();
		if (!pokerFont->loadFromFile("resources/Electrolize-Regular.ttf"))
			printf("Error loading font.");
		sf::RectangleShape *serverBoxRectangle = new sf::RectangleShape();
		serverBoxRectangle->setFillColor(sf::Color(103, 103, 103, 255 * 0.8));
		serverBoxRectangle->setSize(sf::Vector2f(gameWidth*0.95, gameHeight*0.85));
		serverBoxRectangle->setPosition(sf::Vector2f((gameWidth / 2) - (serverBoxRectangle->getLocalBounds().width / 2), (gameHeight / 2) - (serverBoxRectangle->getLocalBounds().height / 2)));

		sf::Text *serverHeading = new sf::Text();
		serverHeading->setFont(*pokerFont);
		serverHeading->setString("Servers");
		serverHeading->setStyle(sf::Text::Italic);
		serverHeading->setCharacterSize(48);
		serverHeading->setPosition(serverBoxRectangle->getGlobalBounds().left + serverBoxRectangle->getLocalBounds().width*0.05, serverBoxRectangle->getGlobalBounds().top + serverBoxRectangle->getLocalBounds().height*0.05);


		serverListBox->setPosition(serverHeading->getGlobalBounds().left, serverHeading->getGlobalBounds().top + serverHeading->getLocalBounds().height * 2);
		serverListBox->setSize(sf::Vector2f(serverBoxRectangle->getLocalBounds().width*0.9, serverBoxRectangle->getLocalBounds().height*0.7));
		
		tgui::Button::Ptr connect_button = theme->load("Button");
		connect_button->setFont(*pokerFont);
		connect_button->setSize(serverBoxRectangle->getLocalBounds().width*0.1, serverBoxRectangle->getLocalBounds().height*0.05);
		connect_button->setPosition(serverListBox->getPosition().x + serverListBox->getSize().x - connect_button->getSize().x,serverListBox->getPosition().y+serverListBox->getSize().y+serverBoxRectangle->getLocalBounds().height*0.025);
		connect_button->setText("Connect");
		connect_button->connect("pressed", [&]() {
			TGUIEvent *newEvent = new TGUIEvent;
			newEvent->eventType = TGUIEvents::JOIN_SERVER;
			newEvent->menu = serverList;
			int serverIndex = serverListBox->getSelectedItemIndex();
			if (serverIndex != -1) {
				UserServer serverToJoin = allServers.at(serverIndex);
				newEvent->arguments = { serverToJoin.ip,std::to_string(serverToJoin.port),serverToJoin.password };
			}
			TGUIEventHandler::events.push_back(newEvent);
		});
		
		tgui::Button::Ptr back_button = theme->load("Button");
		back_button->setFont(*pokerFont);
		back_button->setSize(serverBoxRectangle->getLocalBounds().width*0.1, serverBoxRectangle->getLocalBounds().height*0.05);
		back_button->setPosition(serverListBox->getPosition().x, connect_button->getPosition().y);
		back_button->setText("Back");
		back_button->connect("pressed",[&]() {
			TGUIEvent *event = new TGUIEvent;
			event->menu = serverList;
			event->eventType = TGUIEvents::CHANGE_TO_PLAY_MENU;
			TGUIEventHandler::events.push_back(event);
		});
		
		//The value is going to be the name of the server while the ID is going to be the server ID.
		//serverListBox->addItem("Test test this is server");

		UserServers servers;
		allServers = servers.GetServers();
		std::string stringToAdd;
		for (int c = 0; c < allServers.size(); c++) {
			stringToAdd = "";
			UserServer server = allServers.at(c);
			if (server.passwordProtected)
				stringToAdd += "[PP]";
			stringToAdd += server.name;
			serverListBox->addItem(stringToAdd, std::to_string(server.id));
		}

		serverList.drawings_sfml.push_back(serverBoxRectangle);
		serverList.drawings_sfml.push_back(serverHeading);
		serverList.drawings_tgui.push_back(serverListBox);
		serverList.drawings_tgui.push_back(connect_button);
		serverList.drawings_tgui.push_back(back_button);
		return serverList;
	}
}