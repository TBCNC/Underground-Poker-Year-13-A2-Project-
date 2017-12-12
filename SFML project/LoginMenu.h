#include <SFML/Graphics.hpp>
#include "MenuStructure.h"
#include "TGUIEventHandler.h"
#include <SFML/System.hpp>
#include <TGUI/TGUI.hpp>
#pragma once
namespace GameMenus {
	auto theme = tgui::Theme::create("../TGUI-0.7/widgets/Black.txt");
	MenuStructure menu;
	tgui::EditBox::Ptr login_box = theme->load("EditBox");
	tgui::EditBox::Ptr password_box = theme->load("EditBox");
	MenuStructure LoginScreen(int gameWidth, int gameHeight) {
		//Loading title
		sf::Font *pokerFont = new sf::Font();
		if (!pokerFont->loadFromFile("resources/Electrolize-Regular.ttf"))
			printf("Error loading font.");
		sf::Text *title = new sf::Text();
		title->setFont(*pokerFont);
		title->setString("Underground Poker");
		title->setStyle(sf::Text::Italic);
		title->setCharacterSize(72);
		title->setFillColor(sf::Color::White);
		float textWidth = title->getLocalBounds().width;
		float textHeight = title->getLocalBounds().height;
		title->setPosition(sf::Vector2f((gameWidth / 2) - (textWidth / 2), gameHeight / 20));

		//Setting up login/register form
		sf::RectangleShape* loginrectangle = new sf::RectangleShape();
		loginrectangle->setSize(sf::Vector2f(gameWidth*0.75, gameHeight*0.65));
		loginrectangle->setPosition(sf::Vector2f((gameWidth / 2) - (loginrectangle->getLocalBounds().width / 2), (gameHeight / 2) - (loginrectangle->getLocalBounds().height / 2) + (gameHeight / 20)));
		loginrectangle->setFillColor(sf::Color(103, 103, 103, 255 * 0.6));

		sf::Text *form_title = new sf::Text();
		form_title->setFont(*pokerFont);
		form_title->setString("Login");
		form_title->setCharacterSize(48);
		form_title->setPosition(loginrectangle->getLocalBounds().left + (loginrectangle->getGlobalBounds().width*0.2), loginrectangle->getGlobalBounds().top + loginrectangle->getLocalBounds().height*0.05);
		form_title->setFillColor(sf::Color::White);


		login_box->setPosition(loginrectangle->getGlobalBounds().left + (loginrectangle->getLocalBounds().width*0.025), loginrectangle->getGlobalBounds().top + (loginrectangle->getLocalBounds().height*0.25));
		login_box->setSize(loginrectangle->getLocalBounds().width*0.95, loginrectangle->getLocalBounds().height*0.2);
		login_box->setFont(*pokerFont);
		login_box->setDefaultText("Username");

		password_box->setPosition(loginrectangle->getGlobalBounds().left + (loginrectangle->getLocalBounds().width*0.025), loginrectangle->getGlobalBounds().top + (loginrectangle->getLocalBounds().height*0.5));
		password_box->setSize(loginrectangle->getLocalBounds().width*0.95, loginrectangle->getLocalBounds().height*0.2);
		password_box->setPasswordCharacter('*');
		password_box->setFont(*pokerFont);
		password_box->setDefaultText("Password");

		tgui::Button::Ptr login_button = theme->load("Button");
		login_button->setPosition(loginrectangle->getGlobalBounds().left + (loginrectangle->getLocalBounds().width*0.8), loginrectangle->getGlobalBounds().top + (loginrectangle->getLocalBounds().height*0.8));
		login_button->setSize(loginrectangle->getLocalBounds().width*0.15, loginrectangle->getLocalBounds().height*0.15);
		login_button->setText("Login");

		login_button->connect("pressed", [&]()
		{
			TGUIEvent *eventResult = new TGUIEvent;
			eventResult->eventType = TGUIEvents::LOG_IN;
			eventResult->menu = menu;
			eventResult->arguments.push_back(login_box->getText());
			eventResult->arguments.push_back(password_box->getText());
			TGUIEventHandler::events.push_back(eventResult);
		});

		menu.drawings_sfml.push_back(loginrectangle);
		menu.drawings_sfml.push_back(title);
		menu.drawings_sfml.push_back(form_title);
		menu.drawings_tgui.push_back(login_box);
		menu.drawings_tgui.push_back(password_box);
		menu.drawings_tgui.push_back(login_button);
		return menu;
	}
};