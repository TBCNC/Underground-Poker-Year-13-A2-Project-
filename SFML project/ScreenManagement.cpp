#include "ScreenManagement.h"

ScreenManagement::ScreenManagement(sf::RenderWindow *window_sfml, tgui::Gui *window_tgui) {
	this->window_sfml = window_sfml;
	this->window_tgui = window_tgui;
}
void ScreenManagement::InitializeScreen() {
	this->window_tgui->removeAllWidgets();
	this->DrawTGUI();
}
void ScreenManagement::HandleTGUIEvents()
{
	for(int c=0;c<TGUIEventHandler::events.size();c++)
	{
		int menuIndex = this->menus.size() - 1;
		switch(TGUIEventHandler::events.at(c))
		{
		case TGUIEvents::MESSAGE_BOX_OK:
			//Parse a pointer to this function later
			for(int i=0;i<this->menus.at(menuIndex).drawings_tgui.size();i++)
			{
				this->window_tgui->remove(this->menus.at(menuIndex).drawings_tgui.at(i));
			}
			this->menus.pop_back();//Remove the message box since it will be biggest.
			break;
		case TGUIEvents::LOG_IN:{
			//Log in here
			for(int i=0;i<this->menus.at(menuIndex).drawings_tgui.size();i++)
			{
				this->window_tgui->remove(this->menus.at(menuIndex).drawings_tgui.at(i));
			}
			this->menus.pop_back();
		}
		}
		TGUIEventHandler::events.erase(TGUIEventHandler::events.begin()+c);
	}
}
void ScreenManagement::UpdateScreen() {
	//Event polling
	sf::Event event;
	while (this->window_sfml->pollEvent(event)) {
		this->window_tgui->handleEvent(event);
		if(TGUIEventHandler::events.size()>0)
			this->HandleTGUIEvents();
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