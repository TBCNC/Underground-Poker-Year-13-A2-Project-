#include <SFML/Graphics.hpp>
#include "MenuStructure.h"
#include "ScreenManagement.h"
#include "TGUIEvents.h"
#include "TGUIEventHandler.h"
#pragma once
namespace GameMenus {
	/*
		Right now this is only conceptual art/code.
	*/
	MenuStructure pokerGame;
	MenuStructure PokerGame(int screenWidth, int screenHeight) {
		
		//Cards directory resources\poker_cards_chips_2d\PNGs\cards\Set_B\small

		sf::Font *pokerFont = new sf::Font();
		if (!pokerFont->loadFromFile("resources/Electrolize-Regular.ttf")) {
			printf("Error loading font.");
		}


		sf::RectangleShape *chatRectangle = new sf::RectangleShape();
		chatRectangle->setFillColor(sf::Color(103, 103, 103, 255 * 0.6));
		chatRectangle->setSize(sf::Vector2f(screenWidth*0.35, screenHeight*0.35));
		chatRectangle->setPosition(screenWidth*0.05, screenHeight*0.62);
		pokerGame.drawings_sfml.push_back(chatRectangle);

		tgui::TextBox::Ptr chatBox = theme->load("TextBox");
		chatBox->setFont(*pokerFont);
		chatBox->setText("Test\nAnother message\nAnother message\nAnother message\nomg so many\nmessages\noh wow\nmore");
		chatBox->setReadOnly(true);
		chatBox->setSize(chatRectangle->getLocalBounds().width*0.9, chatRectangle->getLocalBounds().height*0.7);
		chatBox->setPosition(chatRectangle->getGlobalBounds().left + chatRectangle->getLocalBounds().width*0.05, chatRectangle->getGlobalBounds().top + chatRectangle->getLocalBounds().height*0.05);

		tgui::EditBox::Ptr chatMessageBox = theme->load("EditBox");
		chatMessageBox->setSize(chatBox->getSize().x*0.75, chatRectangle->getLocalBounds().height*0.2);
		chatMessageBox->setPosition(chatBox->getPosition().x, chatBox->getPosition().y + chatBox->getSize().y + chatRectangle->getLocalBounds().height*0.025);
		chatMessageBox->setFont(*pokerFont);
		chatMessageBox->setMaximumCharacters(72);
		chatMessageBox->setDefaultText("Type message here...");

		tgui::Button::Ptr sendMessageButton = theme->load("Button");
		sendMessageButton->setFont(*pokerFont);
		sendMessageButton->setText("Send");
		sendMessageButton->setTextSize(24);
		sendMessageButton->setSize(chatBox->getSize().x*0.24, chatMessageBox->getSize().y);
		sendMessageButton->setPosition(chatBox->getPosition().x + chatMessageBox->getSize().x+chatMessageBox->getSize().x*0.01, chatMessageBox->getPosition().y);

		sf::Texture *pokerTableTexture = new sf::Texture();
		if (pokerTableTexture->loadFromFile("resources/pokerTable.png"))
			printf("Could not open poker table.");
		sf::RectangleShape *pokerTableGraphic = new sf::RectangleShape();
		pokerTableGraphic->setTexture(pokerTableTexture);
		pokerTableGraphic->setSize(sf::Vector2f(screenWidth*0.6, screenHeight*0.5));
		pokerTableGraphic->setPosition(screenWidth / 2 - pokerTableGraphic->getLocalBounds().width / 2, screenHeight/2-pokerTableGraphic->getLocalBounds().height/2-chatRectangle->getGlobalBounds().top*0.25);

		sf::Texture *cardTexture = new sf::Texture();
		if (!cardTexture->loadFromFile("resources/poker_cards_chips_2d/PNGs/cards/Set_B/small/card_b_c2.png"))//Again, only conceptual
			printf("Could not open card.");


		sf::RectangleShape *playerCard1 = new sf::RectangleShape();
		sf::RectangleShape *playerCard2 = new sf::RectangleShape();
		playerCard1->setTexture(cardTexture); playerCard2->setTexture(cardTexture);
		playerCard1->setSize(sf::Vector2f(screenWidth*0.1, screenHeight*0.45));
		playerCard2->setSize(sf::Vector2f(screenWidth*0.1, screenHeight*0.45));
		playerCard1->setPosition(chatRectangle->getGlobalBounds().left + chatRectangle->getGlobalBounds().width + screenWidth*0.05, chatRectangle->getGlobalBounds().top);
		playerCard2->setPosition(chatRectangle->getGlobalBounds().left + chatRectangle->getGlobalBounds().width + screenWidth*0.08, chatRectangle->getGlobalBounds().top);

		sf::RectangleShape *foldButton = new sf::RectangleShape();
		foldButton->setFillColor(sf::Color::White);

		pokerGame.drawings_sfml.push_back(chatRectangle);
		pokerGame.drawings_tgui.push_back(chatBox);
		pokerGame.drawings_tgui.push_back(chatMessageBox);
		pokerGame.drawings_tgui.push_back(sendMessageButton);
		pokerGame.drawings_sfml.push_back(pokerTableGraphic);
		pokerGame.drawings_sfml.push_back(playerCard1);
		pokerGame.drawings_sfml.push_back(playerCard2);

		return pokerGame;
	}
}