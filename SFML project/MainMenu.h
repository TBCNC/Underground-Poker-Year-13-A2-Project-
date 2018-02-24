#include <SFML/Graphics.hpp>
#include "MenuStructure.h"
#include "TGUIEventHandler.h"
#include <SFML/System.hpp>
#include <TGUI/TGUI.hpp>
#include "../Network/UserAccount.h"
#pragma once
namespace GameMenus {
	auto mainMenu_Theme = tgui::Theme::create("../TGUI-0.7/widgets/Black.txt");
	MenuStructure mainMenu;
	std::vector<sf::FloatRect> MainMenu_GetBoxes(int gameWidth, int gameHeight) {
		sf::Font *pokerFont = new sf::Font();
		sf::Texture *profilePicture = new sf::Texture();

		if (!pokerFont->loadFromFile("resources/Electrolize-Regular.ttf")) {
			printf("Error loading font.");
		}
		sf::RectangleShape playerRectangle;
		playerRectangle.setFillColor(sf::Color(0, 18, 109, 255 * 0.6));
		playerRectangle.setSize(sf::Vector2f(gameWidth*0.25, gameHeight*0.2));
		playerRectangle.setOutlineColor(sf::Color(117, 117, 117));
		playerRectangle.setOutlineThickness(1.0);
		playerRectangle.setPosition(gameWidth*0.02, gameHeight*0.02);

		sf::RectangleShape statisticsRectangle;
		statisticsRectangle.setFillColor(sf::Color(0, 18, 109, 255 * 0.6));
		statisticsRectangle.setSize(sf::Vector2f(gameWidth*0.25, gameHeight*0.7));
		statisticsRectangle.setOutlineColor(sf::Color(117, 117, 117));
		statisticsRectangle.setOutlineThickness(1.0);
		statisticsRectangle.setPosition(gameWidth*0.02, playerRectangle.getGlobalBounds().top + playerRectangle.getLocalBounds().height);

		sf::RectangleShape announcementsRectangle;
		announcementsRectangle.setFillColor(sf::Color(0, 18, 109, 255 * 0.6));
		announcementsRectangle.setSize(sf::Vector2f(gameWidth*0.65, gameHeight*0.75));
		announcementsRectangle.setOutlineColor(sf::Color(117, 117, 117));
		announcementsRectangle.setOutlineThickness(1.0);
		announcementsRectangle.setPosition(statisticsRectangle.getGlobalBounds().left + statisticsRectangle.getLocalBounds().width + gameWidth*0.02,
			playerRectangle.getGlobalBounds().top + playerRectangle.getLocalBounds().height*0.75);

		sf::RectangleShape option_play;
		option_play.setFillColor(sf::Color(0, 18, 109, 255 * 0.6));
		option_play.setSize(sf::Vector2f(announcementsRectangle.getLocalBounds().width / 3, playerRectangle.getGlobalBounds().height*0.5));
		option_play.setOutlineColor(sf::Color(117, 117, 117));
		option_play.setOutlineThickness(1.0);
		option_play.setPosition(playerRectangle.getGlobalBounds().left + playerRectangle.getLocalBounds().width + gameWidth*0.02, playerRectangle.getGlobalBounds().top);

		sf::RectangleShape option_options;
		option_options.setFillColor(sf::Color(0, 18, 109, 255 * 0.6));
		option_options.setSize(sf::Vector2f(announcementsRectangle.getLocalBounds().width / 3, playerRectangle.getGlobalBounds().height*0.5));
		option_options.setOutlineColor(sf::Color(117, 117, 117));
		option_options.setOutlineThickness(1.0);
		option_options.setPosition(option_play.getGlobalBounds().left + option_play.getLocalBounds().width, playerRectangle.getGlobalBounds().top);

		sf::RectangleShape option_quit;
		option_quit.setFillColor(sf::Color(0, 18, 109, 255 * 0.6));
		option_quit.setSize(sf::Vector2f(announcementsRectangle.getLocalBounds().width / 3, playerRectangle.getGlobalBounds().height*0.5));
		option_quit.setOutlineColor(sf::Color(117, 117, 117));
		option_quit.setOutlineThickness(1.0);
		option_quit.setPosition(option_options.getGlobalBounds().left + option_options.getLocalBounds().width, playerRectangle.getGlobalBounds().top);

		sf::FloatRect rectPlay(option_play.getGlobalBounds().left, option_play.getGlobalBounds().top, option_play.getLocalBounds().width, option_play.getLocalBounds().height);
		sf::FloatRect rectOptions(option_options.getGlobalBounds().left, option_options.getGlobalBounds().top, option_options.getLocalBounds().width, option_options.getLocalBounds().height);
		sf::FloatRect rectQuit(option_quit.getGlobalBounds().left, option_quit.getGlobalBounds().top, option_quit.getLocalBounds().width, option_quit.getLocalBounds().height);

		std::vector<sf::FloatRect> rects = { rectPlay,rectOptions,rectQuit };
		return rects;
	}
	MenuStructure MainMenu(int gameWidth, int gameHeight, UserAccount user) {
		mainMenu.drawings_sfml.clear();
		mainMenu.drawings_tgui.clear();

		sf::Font *pokerFont = new sf::Font();
		sf::Texture *profilePicture = new sf::Texture();

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
		playerRectangle->setOutlineColor(sf::Color(117, 117, 117));
		playerRectangle->setOutlineThickness(1.0);
		playerRectangle->setPosition(gameWidth*0.02, gameHeight*0.02);

		sf::RectangleShape *statisticsRectangle = new sf::RectangleShape();
		statisticsRectangle->setFillColor(sf::Color(0, 18, 109, 255 * 0.6));
		statisticsRectangle->setSize(sf::Vector2f(gameWidth*0.25, gameHeight*0.7));
		statisticsRectangle->setOutlineColor(sf::Color(117, 117, 117));
		statisticsRectangle->setOutlineThickness(1.0);
		statisticsRectangle->setPosition(gameWidth*0.02, playerRectangle->getGlobalBounds().top + playerRectangle->getLocalBounds().height);

		sf::RectangleShape *announcementsRectangle = new sf::RectangleShape();
		announcementsRectangle->setFillColor(sf::Color(0, 18, 109, 255 * 0.6));
		announcementsRectangle->setSize(sf::Vector2f(gameWidth*0.65, gameHeight*0.75));
		announcementsRectangle->setOutlineColor(sf::Color(117, 117, 117));
		announcementsRectangle->setOutlineThickness(1.0);

		

		//announcementsRectangle->setPosition(statisticsRectangle->getGlobalBounds().left + statisticsRectangle->getLocalBounds().width+gameWidth*0.02, statisticsRectangle->getGlobalBounds().top);
		announcementsRectangle->setPosition(statisticsRectangle->getGlobalBounds().left + statisticsRectangle->getLocalBounds().width + gameWidth*0.02,
			playerRectangle->getGlobalBounds().top + playerRectangle->getLocalBounds().height*0.75);

		sf::RectangleShape *option_play = new sf::RectangleShape();
		option_play->setFillColor(sf::Color(0, 18, 109, 255 * 0.6));
		option_play->setSize(sf::Vector2f(announcementsRectangle->getLocalBounds().width/3, playerRectangle->getGlobalBounds().height*0.5));
		option_play->setOutlineColor(sf::Color(117, 117, 117));
		option_play->setOutlineThickness(1.0);
		option_play->setPosition(playerRectangle->getGlobalBounds().left + playerRectangle->getLocalBounds().width + gameWidth*0.02, playerRectangle->getGlobalBounds().top);

		sf::RectangleShape *option_options = new sf::RectangleShape();
		option_options->setFillColor(sf::Color(0, 18, 109, 255 * 0.6));
		option_options->setSize(sf::Vector2f(announcementsRectangle->getLocalBounds().width / 3, playerRectangle->getGlobalBounds().height*0.5));
		option_options->setOutlineColor(sf::Color(117, 117, 117));
		option_options->setOutlineThickness(1.0);
		option_options->setPosition(option_play->getGlobalBounds().left + option_play->getLocalBounds().width, playerRectangle->getGlobalBounds().top);

		sf::RectangleShape *option_quit = new sf::RectangleShape();
		option_quit->setFillColor(sf::Color(0, 18, 109, 255 * 0.6));
		option_quit->setSize(sf::Vector2f(announcementsRectangle->getLocalBounds().width / 3, playerRectangle->getGlobalBounds().height*0.5));
		option_quit->setOutlineColor(sf::Color(117, 117, 117));
		option_quit->setOutlineThickness(1.0);
		option_quit->setPosition(option_options->getGlobalBounds().left + option_options->getLocalBounds().width, playerRectangle->getGlobalBounds().top);

		sf::Text *option_play_text = new sf::Text();
		option_play_text->setFont(*pokerFont);
		option_play_text->setCharacterSize(2 * 0.000017*gameWidth*gameHeight);
		option_play_text->setString("Play");
		option_play_text->setPosition(option_play->getGlobalBounds().left + option_play->getLocalBounds().width / 2 - option_play_text->getLocalBounds().width / 2, option_play->getGlobalBounds().top+ option_play->getLocalBounds().height / 2-option_play_text->getLocalBounds().height*0.625);
		option_play_text->setFillColor(sf::Color::White);
		
		sf::Text *option_options_text = new sf::Text();
		option_options_text->setFont(*pokerFont);
		option_options_text->setCharacterSize(2 * 0.000017*gameWidth*gameHeight);
		option_options_text->setString("Options");
		option_options_text->setPosition(option_options->getGlobalBounds().left + option_options->getLocalBounds().width / 2 - option_options_text->getLocalBounds().width / 2, option_options->getGlobalBounds().top + option_options->getLocalBounds().height / 2 - option_options_text->getLocalBounds().height*0.625);
		option_options_text->setFillColor(sf::Color::White);
	
		sf::Text *option_quit_text = new sf::Text();
		option_quit_text->setFont(*pokerFont);
		option_quit_text->setCharacterSize(2 * 0.000017*gameWidth*gameHeight);
		option_quit_text->setString("Quit");
		option_quit_text->setPosition(option_quit->getGlobalBounds().left + option_quit->getLocalBounds().width / 2 - option_quit_text->getLocalBounds().width / 2, option_quit->getGlobalBounds().top + option_quit->getLocalBounds().height / 2 - option_quit_text->getLocalBounds().height*0.625);
		option_quit_text->setFillColor(sf::Color::White);

		if (!profilePicture->loadFromFile("resources/profilePic.png")) {
			printf("Could not open profile pic.");
		}
		sf::RectangleShape *profilePicture_graphic = new sf::RectangleShape();
		profilePicture_graphic->setTexture(profilePicture);
		profilePicture_graphic->setSize(sf::Vector2f(128, 128));
		profilePicture_graphic->setPosition(playerRectangle->getGlobalBounds().left + (playerRectangle->getLocalBounds().width*0.05), playerRectangle->getGlobalBounds().top + (playerRectangle->getLocalBounds().height*0.1));
		
		//Any text is simply for display and demonstration purposes, implement SQL handling later. Let's just get the display to work.
		sf::Text *playerText = new sf::Text();
		playerText->setFont(*pokerFont);
		playerText->setFillColor(sf::Color::White);
		playerText->setCharacterSize(0.000017*gameWidth*gameHeight);
		playerText->setString(user.username + "\nELO Rank:" + std::to_string(user.ELO));
		playerText->setPosition(profilePicture_graphic->getGlobalBounds().left + profilePicture_graphic->getLocalBounds().width + playerRectangle->getLocalBounds().width*0.05, profilePicture_graphic->getGlobalBounds().top+profilePicture_graphic->getLocalBounds().height*0.02);

		sf::Text *statisticsText_Heading = new sf::Text();
		statisticsText_Heading->setFont(*pokerFont);
		statisticsText_Heading->setFillColor(sf::Color::White);
		statisticsText_Heading->setCharacterSize(1.5*0.000017*gameWidth*gameHeight);
		statisticsText_Heading->setString("Player statistics");
		statisticsText_Heading->setPosition(profilePicture_graphic->getGlobalBounds().left, playerRectangle->getLocalBounds().height + playerRectangle->getGlobalBounds().top + (0.01*statisticsRectangle->getLocalBounds().height));

		sf::Text *statisticsText = new sf::Text();
		statisticsText->setFont(*pokerFont);
		statisticsText->setFillColor(sf::Color::White);
		statisticsText->setCharacterSize(1*0.000017*gameWidth*gameHeight);
		//statisticsText->setString("Rounds won:247\nGames won:102\nGames lost:89\nWin-Loss ratio:1.15\nTimes knocked out:12\n\nCompetitive games won:27\nCompetitive games lost:32\nRatio:0.84375");
		statisticsText->setString("\nRounds won:" + std::to_string(user.userStats.rounds_won) + "\nGames won:"+std::to_string(user.userStats.games_won)+"\nGames lost:"+std::to_string(user.userStats.games_lost)+"\nWin-Loss ratio"+std::to_string(user.userStats.wintoloss_games)+"\n\nCompetitive games:"+std::to_string(user.userStats.comps_won)+"\nCompetitive games lost:"+std::to_string(user.userStats.comps_lost)+"\nWin-Loss ratio:"+std::to_string(user.userStats.wintoloss_comps));
		statisticsText->setPosition(statisticsText_Heading->getGlobalBounds().left, statisticsText->getGlobalBounds().top + statisticsText->getLocalBounds().height + (statisticsRectangle->getLocalBounds().height*0.02));

		sf::Text *announcementsText_Heading = new sf::Text();
		announcementsText_Heading->setFont(*pokerFont);
		announcementsText_Heading->setFillColor(sf::Color::White);
		announcementsText_Heading->setCharacterSize(1.5*0.000017*gameWidth*gameHeight);
		announcementsText_Heading->setString("First message ever in Underground Poker!");
		announcementsText_Heading->setPosition(announcementsRectangle->getGlobalBounds().left + (announcementsRectangle->getLocalBounds().width*0.03), announcementsRectangle->getGlobalBounds().top + (announcementsRectangle->getLocalBounds().height*0.03));

		sf::Text *announcementsText = new sf::Text();
		announcementsText->setFont(*pokerFont);
		announcementsText->setFillColor(sf::Color::White);
		announcementsText->setCharacterSize(0.000017*gameWidth*gameHeight);
		announcementsText->setString("This is the first announcement message, ever!\nHere are some things that I need to do:\n-Finish this game\n-Fix memory bugs\n-Do other cool things!");
		announcementsText->setPosition(announcementsText_Heading->getGlobalBounds().left, announcementsText_Heading->getGlobalBounds().top + announcementsText_Heading->getLocalBounds().height + announcementsRectangle->getLocalBounds().height*0.03);

		mainMenu.drawings_sfml.push_back(playerRectangle);
		mainMenu.drawings_sfml.push_back(profilePicture_graphic);
		mainMenu.drawings_sfml.push_back(statisticsRectangle);
		mainMenu.drawings_sfml.push_back(playerText);
		mainMenu.drawings_sfml.push_back(statisticsText_Heading);
		mainMenu.drawings_sfml.push_back(statisticsText);
		mainMenu.drawings_sfml.push_back(announcementsRectangle);
		mainMenu.drawings_sfml.push_back(announcementsText_Heading);
		mainMenu.drawings_sfml.push_back(announcementsText);
		mainMenu.drawings_sfml.push_back(option_play);
		mainMenu.drawings_sfml.push_back(option_options);
		mainMenu.drawings_sfml.push_back(option_quit);
		mainMenu.drawings_sfml.push_back(option_play_text);
		mainMenu.drawings_sfml.push_back(option_options_text);
		mainMenu.drawings_sfml.push_back(option_quit_text);
		return mainMenu;
	}
}