#include "Game.h"
#include "MessageBox.h"

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
	ScreenManagement screen_management(this->window, this->gui);
	screen_management.menus.push_back(GameMenus::BackgroundImage(this->width, this->height));
	screen_management.menus.push_back(GameMenus::MessageBox("This game is for 18+ only, faggots.",GameMenus::INFORMATION,GameMenus::OK,this->width,this->height));
	screen_management.InitializeScreen();
	while (window.isOpen()) {	
		screen_management.UpdateScreen();
	}
}
void Game::ManageEvent(sf::Event event) {
	if (event.type == sf::Event::Closed)
		this->window->close();
}