#include "MenuStructure.h"
#include "TGUIEvents.h"
#include "TGUIEventHandler.h"
#include "../Network/Client.h"
#include "../Network/PacketType.h"
#include "../Network/Server.h"
#include "../Network/UserAccount.h"
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <thread>
#include <vector>
#pragma once

///<sumamry>
///This class is used to manage and present items onto the screen such as menus and boxes.
///</summary>
enum MenuTypes:int{
	LOG_IN_MENU=0,
	MESSAGE_BOX=1,
	MAIN_MENU=2,
	SERVER_LIST=3,
	POKER_GAME=4,
};
class ScreenManagement : TGUIEventHandler{
public:
	ScreenManagement(sf::RenderWindow *window_sfml, tgui::Gui *window_tgui);
	~ScreenManagement();
	std::vector <MenuStructure> menus;
	void InitializeScreen();
	void UpdateScreen();
private:
	void SFMLEventHandler(sf::Event event);
	void DrawSFML();
	void DrawTGUI();
	void HandleClientEvents();//This function assumes we are in game
	void HandleTGUIEvents();
	void HandleSFMLEvents();//This is specifically for SFML buttons/rectangles
	void AddMenu(MenuStructure menu);
	void RemoveMenu(MenuStructure menu);
	int FindIndexOfMenu(MenuStructure menu);
	std::vector<sf::FloatRect> pokerBoundaries;//Used when in game
	std::vector<std::string> chatHistory;//Used when in game
	std::vector<Player*> currentPlayers;//Used when in game
	std::vector<Card> userCards;
	std::vector<Card> tableCards;
	bool usersTurn = false;//Used when in game
	MenuTypes currentMenu;
	sf::RenderWindow *window_sfml;
	tgui::Gui *window_tgui;
	UserAccount user;
	Client *client;
	
	bool mouseOn = false;
};