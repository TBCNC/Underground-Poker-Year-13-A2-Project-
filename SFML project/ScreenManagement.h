#include "MenuStructure.h"
#include "TGUIEvents.h"
#include "TGUIEventHandler.h"
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <vector>
#pragma once

///<sumamry>
///This class is used to manage and present items onto the screen such as menus and boxes.
///</summary>

class ScreenManagement {
public:
	ScreenManagement(sf::RenderWindow *window_sfml, tgui::Gui *window_tgui);
	std::vector <MenuStructure> menus;
	void InitializeScreen();
	void UpdateScreen();
private:
	void SFMLEventHandler(sf::Event event);
	void DrawSFML();
	void DrawTGUI();
	void HandleTGUIEvents();
	void RemoveMenu(MenuStructure menu);
	int FindIndexOfMenu(MenuStructure menu);
	sf::RenderWindow *window_sfml;
	tgui::Gui *window_tgui;
};