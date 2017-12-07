#include "ScreenManagement.h"

ScreenManagement::ScreenManagement(sf::RenderWindow *window_sfml, tgui::Gui *window_tgui) {
	this->window_sfml = window_sfml;
	this->window_tgui = window_tgui;
}
void ScreenManagement::InitializeScreen() {
	this->window_tgui->removeAllWidgets();
	this->DrawTGUI();
}
void ScreenManagement::UpdateScreen() {
	//Event polling
	sf::Event event;
	while (this->window_sfml->pollEvent(event)) {
		//Create an event manager class and place it here
		this->window_tgui->handleEvent(event);
	}
	//Graphical drawing
	this->window_sfml->clear();
	this->DrawSFML();
	this->window_tgui->draw();
	this->window_sfml->display();
}
void ScreenManagement::DrawSFML() {
	for (int menuCounter = 0; menuCounter < this->menus.size(); menuCounter++) {
		MenuStructure currentMenu = this->menus.at(menuCounter);
		for (int sfmlCounter = 0; sfmlCounter < currentMenu.drawings_sfml.size(); sfmlCounter++) {
			this->window_sfml->draw(*currentMenu.drawings_sfml.at(sfmlCounter));
		}
	}
}
void ScreenManagement::DrawTGUI() {
	for (int menuCounter = 0; menuCounter < this->menus.size(); menuCounter++) {
		MenuStructure currentMenu = this->menus.at(menuCounter);
		for (int tguiCounter = 0; tguiCounter < currentMenu.drawings_tgui.size(); tguiCounter++) {
			this->window_tgui->add(currentMenu.drawings_tgui.at(tguiCounter));
		}
	}
}