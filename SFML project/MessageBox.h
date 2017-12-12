#include <SFML/Graphics.hpp>
#include "MenuStructure.h"
#include "ScreenManagement.h"
#include "TGUIEvents.h"
#include "TGUIEventHandler.h"
#pragma once
namespace GameMenus {
	enum MessageType : int {
		ERROR = 0,
		WARNING = 1,
		INFORMATION = 2
	};
	enum BoxType : int {
		OK = 0,
		YESNO = 1
	};

	MenuStructure msgBox;
	MenuStructure MessageBox(sf::String msg, MessageType message_type, BoxType box_type, int screen_width, int screen_height)
	{
		msgBox.drawings_sfml.clear();
		msgBox.drawings_tgui.clear();
		auto theme = tgui::Theme::create("../TGUI-0.7/widgets/Black.txt");

		sf::RectangleShape *messageBox = new sf::RectangleShape();
		messageBox->setSize(sf::Vector2f(screen_width*0.5, screen_height*0.35));
		messageBox->setPosition(sf::Vector2f(screen_width / 2 - (screen_width*0.5/2), screen_height / 2 - (screen_height*0.35/2)));
		messageBox->setOutlineColor(sf::Color::Black);
		messageBox->setFillColor(sf::Color(103, 103, 103, 255 * 0.6));

		sf::Font *font = new sf::Font();
		font->loadFromFile("resources/Electrolize-Regular.ttf");
		
		sf::Text *titleText = new sf::Text();
		switch(message_type)
		{
		case MessageType::ERROR:
			{
			titleText->setString("ERROR!");
			break;
			}
		case MessageType::WARNING:
			{
			titleText->setString("WARNING!");
			break;
			}
		case MessageType::INFORMATION:
			{
			titleText->setString("INFORMATION");
			}
		}
		titleText->setCharacterSize(32);
		titleText->setFont(*font);
		titleText->setPosition((messageBox->getGlobalBounds().left)+(messageBox->getLocalBounds().width / 2) - (titleText->getLocalBounds().width / 2), messageBox->getGlobalBounds().top*1.1);
		titleText->setFillColor(sf::Color::White);

		sf::Text *messageText = new sf::Text();
		messageText->setCharacterSize(24);
		messageText->setFont(*font);
		messageText->setString(msg);
		messageText->setPosition((messageBox->getGlobalBounds().left) + (messageBox->getLocalBounds().width / 2) - (messageText->getLocalBounds().width / 2), messageBox->getGlobalBounds().top*1.45);
		messageText->setFillColor(sf::Color::White);
		//Let's just focus on OK buttons for now and worry about Yes and No later.

		tgui::Button::Ptr okButton = theme->load("Button");
		okButton->setSize(messageBox->getLocalBounds().width*0.3, messageBox->getLocalBounds().height*0.15);
		okButton->setPosition((messageBox->getGlobalBounds().left) + (messageBox->getLocalBounds().width / 2)-(okButton->getSize().x/2), messageBox->getGlobalBounds().top*1.8);
		okButton->setText("OK");
		okButton->setFont(*font);
		okButton->setTextSize(32);

		msgBox.drawings_sfml.push_back(messageBox);
		msgBox.drawings_sfml.push_back(titleText);
		msgBox.drawings_sfml.push_back(messageText);
		msgBox.drawings_tgui.push_back(okButton);

		//For write up, by putting the code inside the okbutton connect outside of here this causes errors. Talk about how I solved this error

		okButton->connect("pressed", [&]()
		{
			TGUIEvent *eventResult = new TGUIEvent;
			eventResult->eventType = TGUIEvents::MESSAGE_BOX_OK;
			eventResult->menu = msgBox;
			eventResult->arguments.push_back("test");
			TGUIEventHandler::events.push_back(eventResult);
		});

		return msgBox;
	}
}