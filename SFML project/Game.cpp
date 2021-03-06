#include "Game.h"
//#include "TGUIEventHandler.h"


Game::Game(int width, int height, bool AA) {
	this->width = width;
	this->height = height;
	this->AA = AA;
}
void Game::Run() {
	sf::RenderWindow window(sf::VideoMode(this->width, this->height), "Underground poker");
	tgui::Gui gui(window);
	this->window = &window;
	this->gui = &gui;
	window.setFramerateLimit(60);
	TGUIEventHandler handler;
	ScreenManagement screen_management(this->window, this->gui);
	screen_management.InitializeScreen();
	while (window.isOpen()) {	
		screen_management.UpdateScreen();
	}
	std::cout << "Closing window..." << std::endl;
}