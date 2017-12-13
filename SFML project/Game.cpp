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
	screen_management.menus.push_back(GameMenus::LoginScreen(this->width, this->height));
	//screen_management.menus.push_back(GameMenus::MessageBox("Hello world!",GameMenus::MessageType::INFORMATION,GameMenus::BoxType::YESNO,this->width,this->height));
	screen_management.InitializeScreen();
	while (window.isOpen()) {	
		screen_management.UpdateScreen();
	}
}