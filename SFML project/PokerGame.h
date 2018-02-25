#include <SFML/Graphics.hpp>
#include "MenuStructure.h"
#include "ScreenManagement.h"
#include "TGUIEvents.h"
#include "TGUIEventHandler.h"
#include "../Network/UserAccount.h"
#pragma once
namespace GameMenus {
	/*
		Right now this is only conceptual art/code.
	*/
	MenuStructure pokerGame;
	tgui::EditBox::Ptr chatMessageBox = theme->load("EditBox");
	int sliderWheelVal = 100;
	tgui::Slider::Ptr pointSlider = theme->load("Slider");
	sf::Text *sliderText = new sf::Text();
	std::string GetCardTexture(Card card, bool small=true) {//Returns the file destination for the cards
		std::string initialDir;
		if (small)
			initialDir = "resources\\poker_cards_chips_2d\\PNGs\\cards\\Set_B\\small\\";
		else
			initialDir = "resources\\poker_cards_chips_2d\\PNGs\\cards\\Set_B\\large\\";
		std::string suitIndicator="";
		switch (card.card_suit) {
		case CLUBS:
			suitIndicator = "c";
			break;
		case HEARTS:
			suitIndicator = "h";
			break;
		case DIAMONDS:
			suitIndicator = "d";
			break;
		case SPADES:
			suitIndicator = "s";
			break;
		}
		std::string cardValue = "";
		if (card.card_value > 10) {
			if (card.card_value == JACK)
				cardValue = "j";
			else if (card.card_value == QUEEN)
				cardValue = "q";
			else if (card.card_value == KING)
				cardValue = "k";
		}
		else if (card.card_value == 1)
			cardValue = "a";
		else
			cardValue = std::to_string(card.card_value);
		if (small)
			return initialDir + "card_b_" + suitIndicator + cardValue + ".png";
		else
			return initialDir + "card_b_" + suitIndicator + cardValue + "_large.png";
	}
	MenuStructure PokerGame(int screenWidth, int screenHeight, bool userTurn, std::vector<sf::FloatRect> *boundaries, std::vector<std::string> chatBoxText = {}, std::vector<Player*> players = {}, std::vector<Card> cards_player = {}, std::vector<Card> cards_table = {}) {

		//Cards directory resources\poker_cards_chips_2d\PNGs\cards\Set_B\small
		pokerGame.drawings_sfml.clear();
		pokerGame.drawings_tgui.clear();
		boundaries->clear();

		sf::Font *pokerFont = new sf::Font();
		if (!pokerFont->loadFromFile("resources/Electrolize-Regular.ttf")) {
			printf("Error loading font.");
		}

		sf::RectangleShape *chatRectangle = new sf::RectangleShape();
		chatRectangle->setFillColor(sf::Color(103, 103, 103, 255 * 0.6));
		chatRectangle->setSize(sf::Vector2f(screenWidth*0.35, screenHeight*0.35));
		chatRectangle->setPosition(screenWidth*0.05, screenHeight*0.62);
		pokerGame.drawings_sfml.push_back(chatRectangle);

		tgui::ListBox::Ptr chatBox = theme->load("ListBox");
		chatBox->setFont(*pokerFont);
		chatBox->setSize(chatRectangle->getLocalBounds().width*0.9, chatRectangle->getLocalBounds().height*0.7);
		chatBox->setPosition(chatRectangle->getGlobalBounds().left + chatRectangle->getLocalBounds().width*0.05, chatRectangle->getGlobalBounds().top + chatRectangle->getLocalBounds().height*0.05);
		if (chatBoxText.size() > 0) {
			int maxItems = floor(chatBox->getSize().y / chatBox->getItemHeight());
			if (chatBoxText.size() <= maxItems) {
				for (int c = maxItems - 1; c >= 0; c--) {
					if (c >= chatBoxText.size()) {
						chatBox->addItem("");
					}
					else {
						chatBox->addItem(chatBoxText.at(chatBoxText.size()-c-1));
					}
				}
			}
			else {
				for (int c = chatBoxText.size() - 1; c >= chatBoxText.size() - (maxItems + 1); c--) {
					chatBox->addItem(chatBoxText.at(c));
				}
			}
		}

		chatMessageBox->setSize(chatBox->getSize().x*0.75, chatRectangle->getLocalBounds().height*0.2);
		chatMessageBox->setPosition(chatBox->getPosition().x, chatBox->getPosition().y + chatBox->getSize().y + chatRectangle->getLocalBounds().height*0.025);
		chatMessageBox->setFont(*pokerFont);
		chatMessageBox->setMaximumCharacters(72);
		chatMessageBox->setText("");
		chatMessageBox->setDefaultText("Type message here...");

		tgui::Button::Ptr sendMessageButton = theme->load("Button");
		sendMessageButton->setFont(*pokerFont);
		sendMessageButton->setText("Send");
		sendMessageButton->setTextSize(24);
		sendMessageButton->setSize(chatBox->getSize().x*0.24, chatMessageBox->getSize().y);
		sendMessageButton->setPosition(chatBox->getPosition().x + chatMessageBox->getSize().x + chatMessageBox->getSize().x*0.01, chatMessageBox->getPosition().y);
		sendMessageButton->connect("pressed", [&]() {
			TGUIEvent *eventResult = new TGUIEvent;
			eventResult->eventType = TGUIEvents::SEND_CHAT_MESSAGE;
			eventResult->menu = menu;
			eventResult->arguments.push_back(chatMessageBox->getText());
			TGUIEventHandler::events.push_back(eventResult);
		});

		sf::Texture *pokerTableTexture = new sf::Texture();
		if (!pokerTableTexture->loadFromFile("resources/pokerTable.png"))
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
		//playerCard1->setTexture(cardTexture); playerCard2->setTexture(cardTexture);
		playerCard1->setSize(sf::Vector2f(screenWidth*0.1, screenHeight*0.45));
		playerCard2->setSize(sf::Vector2f(screenWidth*0.1, screenHeight*0.45));
		playerCard1->setPosition(chatRectangle->getGlobalBounds().left + chatRectangle->getGlobalBounds().width + screenWidth*0.05, chatRectangle->getGlobalBounds().top);
		playerCard2->setPosition(chatRectangle->getGlobalBounds().left + chatRectangle->getGlobalBounds().width + screenWidth*0.08, chatRectangle->getGlobalBounds().top);
		if (cards_player.size() > 0) {
			sf::Texture *card1Text = new sf::Texture();
			sf::Texture *card2Text = new sf::Texture();
			card1Text->loadFromFile(GetCardTexture(cards_player.at(0), false));
			card2Text->loadFromFile(GetCardTexture(cards_player.at(1), false));
			playerCard1->setTexture(card1Text);
			playerCard2->setTexture(card2Text);
		}

		sf::RectangleShape *foldButton = new sf::RectangleShape();
		foldButton->setFillColor(sf::Color(255,255,255,255*0.8));
		foldButton->setSize(sf::Vector2f((playerCard2->getLocalBounds().width + playerCard2->getGlobalBounds().left)*0.17, chatMessageBox->getSize().y));
		foldButton->setPosition(playerCard2->getGlobalBounds().left + playerCard2->getLocalBounds().width + screenWidth*0.05, chatMessageBox->getPosition().y);

		sf::RectangleShape *callButton = new sf::RectangleShape();
		callButton->setFillColor(sf::Color(255, 255, 255, 255 * 0.8));
		callButton->setSize(sf::Vector2f((playerCard2->getLocalBounds().width + playerCard2->getGlobalBounds().left)*0.17, chatMessageBox->getSize().y));
		callButton->setPosition(foldButton->getGlobalBounds().left + foldButton->getLocalBounds().width + screenWidth*0.01, chatMessageBox->getPosition().y);

		sf::RectangleShape *raiseButton = new sf::RectangleShape();
		raiseButton->setFillColor(sf::Color(255, 255, 255, 255 * 0.8));
		raiseButton->setSize(sf::Vector2f((playerCard2->getLocalBounds().width + playerCard2->getGlobalBounds().left)*0.17, chatMessageBox->getSize().y));
		raiseButton->setPosition(callButton->getGlobalBounds().left + callButton->getLocalBounds().width + screenWidth*0.01, chatMessageBox->getPosition().y);

		sf::FloatRect foldBoundaries(foldButton->getGlobalBounds().left, foldButton->getGlobalBounds().top, foldButton->getLocalBounds().width, foldButton->getLocalBounds().height);
		sf::FloatRect callBoundaries(callButton->getGlobalBounds().left, callButton->getGlobalBounds().top, callButton->getLocalBounds().width, callButton->getLocalBounds().height);
		sf::FloatRect raiseBoundaries(raiseButton->getGlobalBounds().left, raiseButton->getGlobalBounds().top, raiseButton->getLocalBounds().width, raiseButton->getLocalBounds().height);

		boundaries->push_back(foldBoundaries);
		boundaries->push_back(callBoundaries);
		boundaries->push_back(raiseBoundaries);

		sf::Text *foldButtonText = new sf::Text();
		sf::Text *callButtonText = new sf::Text();
		sf::Text *raiseButtonText = new sf::Text();
		foldButtonText->setCharacterSize(1.5*0.000017*screenWidth*screenHeight);
		callButtonText->setCharacterSize(1.5*0.000017*screenWidth*screenHeight);
		raiseButtonText->setCharacterSize(1.5*0.000017*screenWidth*screenHeight);
		foldButtonText->setFillColor(sf::Color::Black);
		callButtonText->setFillColor(sf::Color::Black);
		raiseButtonText->setFillColor(sf::Color::Black);
		foldButtonText->setFont(*pokerFont);
		callButtonText->setFont(*pokerFont);
		raiseButtonText->setFont(*pokerFont);

		sf::FloatRect *sliderContainer = new sf::FloatRect();
		if (userTurn) {
			foldButtonText->setString("Fold");
			foldButtonText->setPosition((foldButton->getGlobalBounds().left + foldButton->getLocalBounds().width / 2) - foldButtonText->getLocalBounds().width / 2, (foldButton->getGlobalBounds().top + foldButton->getLocalBounds().height / 2) - 3 * foldButtonText->getLocalBounds().height / 4);
			callButtonText->setString("Call");
			callButtonText->setPosition((callButton->getGlobalBounds().left + callButton->getLocalBounds().width / 2) - callButtonText->getLocalBounds().width / 2, (callButton->getGlobalBounds().top + callButton->getLocalBounds().height / 2) - 3 * callButtonText->getLocalBounds().height / 4);
			raiseButtonText->setString("Raise");
			raiseButtonText->setPosition((raiseButton->getGlobalBounds().left + raiseButton->getLocalBounds().width / 2) - raiseButtonText->getLocalBounds().width / 2, (raiseButton->getGlobalBounds().top + raiseButton->getLocalBounds().height / 2) - 3 * raiseButtonText->getLocalBounds().height / 4);

			pointSlider->setMinimum(10);
			pointSlider->setMaximum(1000);
			pointSlider->setSize((raiseButton->getGlobalBounds().left + raiseButton->getLocalBounds().width) - foldButton->getGlobalBounds().left, foldButton->getLocalBounds().height*0.25);
			pointSlider->setPosition(foldButton->getGlobalBounds().left, chatBox->getPosition().y + chatBox->getSize().y*0.85);
			pointSlider->setValue(sliderWheelVal);
			pointSlider->connect("ValueChanged", [&](int slideVal) {
				sliderText->setString(std::to_string(slideVal));
			},std::bind(&tgui::Slider::getValue,pointSlider));

			sliderText->setFont(*pokerFont);
			sliderText->setCharacterSize(0.000017*screenWidth*screenHeight);
			sliderText->setPosition(sf::Vector2f(pointSlider->getPosition().x + pointSlider->getSize().x*0.9, pointSlider->getPosition().y - pointSlider->getSize().y * 2));
			sliderText->setString(std::to_string(pointSlider->getValue()));

			sliderContainer->width = pointSlider->getSize().x;
			sliderContainer->height = pointSlider->getSize().y;
			sliderContainer->left = pointSlider->getPosition().x;
			sliderContainer->top = pointSlider->getPosition().y;
		}
		std::vector<sf::Drawable*> playerItems;
		if (players.size() > 0) {
			float centreOfTableY = pokerTableGraphic->getLocalBounds().height / 2;
			float changeConstant = pokerTableGraphic->getLocalBounds().height / 3;
			for (int c = 0; c < players.size(); c++) {//Max players is 6
				if (c < 3) {
					sf::Text *playerText = new sf::Text();
					playerText->setFont(*pokerFont);
					playerText->setCharacterSize(1.5*0.000017*screenWidth*screenHeight);
					playerText->setFillColor(sf::Color::Black);
					if(c==0||c==2)
						playerText->setPosition(pokerTableGraphic->getGlobalBounds().left - pokerTableGraphic->getLocalBounds().width*0.1, centreOfTableY - changeConstant + (changeConstant*c));
					else
						playerText->setPosition(pokerTableGraphic->getGlobalBounds().left - pokerTableGraphic->getLocalBounds().width*0.2, centreOfTableY - changeConstant + (changeConstant*c));
					playerText->setString(players.at(c)->user.username);
					sf::RectangleShape *profilePicture = new sf::RectangleShape();
					sf::Texture *profileTexture = new sf::Texture();
					if (!profileTexture->loadFromFile(players.at(c)->user.profilePicture)) {
						std::cout << "Could not open profile pic" << std::endl;
					}
					profilePicture->setSize(sf::Vector2f(64,64));
					profilePicture->setTexture(profileTexture);
					profilePicture->setPosition(playerText->getGlobalBounds().left + playerText->getLocalBounds().width / 2 - 32, playerText->getGlobalBounds().top + 32);
					sf::Text *scoreText = new sf::Text();
					scoreText->setFont(*pokerFont);
					scoreText->setCharacterSize(1.5*0.000017*screenWidth*screenHeight);
					scoreText->setFillColor(sf::Color::Black);
					scoreText->setString(std::to_string(players.at(c)->points));
					scoreText->setPosition(playerText->getGlobalBounds().left+playerText->getLocalBounds().width/2-scoreText->getLocalBounds().width/2, profilePicture->getGlobalBounds().top + profilePicture->getLocalBounds().height + 8);
					
					playerItems.push_back(playerText);
					playerItems.push_back(profilePicture);
					playerItems.push_back(scoreText);

					if (!players.at(c)->playing) {
						sf::RectangleShape *foldRectangle = new sf::RectangleShape();
						sf::Text *bustText = new sf::Text();
						bustText->setFont(*pokerFont);
						foldRectangle->setSize(sf::Vector2f(playerText->getLocalBounds().width, playerText->getLocalBounds().height*1.1));
						foldRectangle->setPosition(playerText->getGlobalBounds().left + playerText->getLocalBounds().width / 2 - foldRectangle->getLocalBounds().width / 2, profilePicture->getGlobalBounds().top + profilePicture->getLocalBounds().height / 2 - foldRectangle->getLocalBounds().height / 2);
						foldRectangle->setFillColor(sf::Color::White);
						foldRectangle->setOutlineColor(sf::Color::Black);
						foldRectangle->setOutlineThickness(2);
						bustText->setFillColor(sf::Color::Red);
						bustText->setCharacterSize(1.5*0.000017*screenWidth*screenHeight);
						bustText->setString("FOLDED");
						bustText->setPosition(foldRectangle->getGlobalBounds().left + foldRectangle->getLocalBounds().width / 2 - bustText->getLocalBounds().width / 2, foldRectangle->getGlobalBounds().top + foldRectangle->getLocalBounds().height / 2 - bustText->getLocalBounds().height / 2);
					}
				}
				else {
					sf::Text *playerText = new sf::Text();
					playerText->setFont(*pokerFont);
					playerText->setCharacterSize(1.5*0.000017*screenWidth*screenHeight);
					playerText->setFillColor(sf::Color::Black);
					if (c == 0 || c == 2)
						playerText->setPosition(pokerTableGraphic->getGlobalBounds().left + pokerTableGraphic->getLocalBounds().width + pokerTableGraphic->getLocalBounds().width*0.1, centreOfTableY - changeConstant + (changeConstant*c));
					else
						playerText->setPosition(pokerTableGraphic->getGlobalBounds().left + pokerTableGraphic->getLocalBounds().width + pokerTableGraphic->getLocalBounds().width*0.2, centreOfTableY - changeConstant + (changeConstant*c));
					playerText->setString(players.at(c)->user.username);
					sf::RectangleShape *profilePicture = new sf::RectangleShape();
					sf::Texture *profileTexture = new sf::Texture();
					if (!profileTexture->loadFromFile(players.at(c)->user.profilePicture)) {
						std::cout << "Could not open profile pic" << std::endl;
					}
					profilePicture->setSize(sf::Vector2f(64, 64));
					profilePicture->setTexture(profileTexture);
					profilePicture->setPosition(playerText->getGlobalBounds().left + playerText->getLocalBounds().width / 2 - 32, playerText->getGlobalBounds().top + 32);
					sf::Text *scoreText = new sf::Text();
					scoreText->setFont(*pokerFont);
					scoreText->setCharacterSize(1.5*0.000017*screenWidth*screenHeight);
					scoreText->setFillColor(sf::Color::Black);
					scoreText->setString(std::to_string(players.at(c)->points));
					scoreText->setPosition(playerText->getGlobalBounds().left + playerText->getLocalBounds().width / 2 - scoreText->getLocalBounds().width / 2, profilePicture->getGlobalBounds().top + profilePicture->getLocalBounds().height + 8);

					playerItems.push_back(playerText);
					playerItems.push_back(profilePicture);
					playerItems.push_back(scoreText);
				}
			}
		}

		pokerGame.drawings_sfml.push_back(chatRectangle);
		pokerGame.drawings_tgui.push_back(chatBox);
		pokerGame.drawings_tgui.push_back(chatMessageBox);
		pokerGame.drawings_tgui.push_back(sendMessageButton);
		pokerGame.drawings_sfml.push_back(pokerTableGraphic);
		if(cards_player.size()>1)
			pokerGame.drawings_sfml.push_back(playerCard1);
			pokerGame.drawings_sfml.push_back(playerCard2);
		if (userTurn) {
			pokerGame.drawings_sfml.push_back(foldButton);
			pokerGame.drawings_sfml.push_back(callButton);
			pokerGame.drawings_sfml.push_back(raiseButton);
			pokerGame.drawings_sfml.push_back(foldButtonText);
			pokerGame.drawings_sfml.push_back(callButtonText);
			pokerGame.drawings_sfml.push_back(raiseButtonText);
			pokerGame.drawings_tgui.push_back(pointSlider);
			pokerGame.drawings_sfml.push_back(sliderText);
		}
		for (int c = 0; c < playerItems.size(); c++) {
			pokerGame.drawings_sfml.push_back(playerItems.at(c));
		}
		sf::RectangleShape *lastCard = new sf::RectangleShape();
		for (int c = 0; c < cards_table.size(); c++) {
			if (c == 0) {
				sf::RectangleShape *tableCard = new sf::RectangleShape();
				tableCard->setSize(sf::Vector2f(pokerTableGraphic->getLocalBounds().width*0.15, pokerTableGraphic->getLocalBounds().height*0.4));
				tableCard->setPosition(pokerTableGraphic->getGlobalBounds().left + pokerTableGraphic->getLocalBounds().width*(0.1), pokerTableGraphic->getGlobalBounds().top + pokerTableGraphic->getLocalBounds().height*0.3);
				sf::Texture *cardTexture = new sf::Texture();
				cardTexture->loadFromFile(GetCardTexture(cards_table.at(c)));
				tableCard->setTexture(cardTexture);
				pokerGame.drawings_sfml.push_back(tableCard);
				lastCard = tableCard;
			}
			else {
				sf::RectangleShape *tableCard = new sf::RectangleShape();
				tableCard->setSize(sf::Vector2f(pokerTableGraphic->getLocalBounds().width*0.15, pokerTableGraphic->getLocalBounds().height*0.4));
				tableCard->setPosition(lastCard->getGlobalBounds().left+lastCard->getLocalBounds().width+pokerTableGraphic->getLocalBounds().width*0.05, pokerTableGraphic->getGlobalBounds().top + pokerTableGraphic->getLocalBounds().height*0.3);
				sf::Texture *cardTexture = new sf::Texture();
				cardTexture->loadFromFile(GetCardTexture(cards_table.at(c)));
				tableCard->setTexture(cardTexture);
				pokerGame.drawings_sfml.push_back(tableCard);
				lastCard = tableCard;
			}
		}
		return pokerGame;
	}

}