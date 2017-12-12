#include "ScreenManagement.h"
#include "MessageBox.h"

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
		MenuStructure msgBox2;
		switch(TGUIEventHandler::events.at(c)->eventType)
		{
		case TGUIEvents::MESSAGE_BOX_OK:
			RemoveMenu(TGUIEventHandler::events.at(c)->menu);
			break;
		case TGUIEvents::LOG_IN:
			RemoveMenu(TGUIEventHandler::events.at(c)->menu);
			//Log in the user here Index 0=Username Index 1=Password
			//Display a status box that updates as the user is being logged in
			MenuStructure msgBox = GameMenus::MessageBox("Logged in successfully!", GameMenus::MessageType::INFORMATION, GameMenus::BoxType::OK, this->window_sfml->getSize().x, this->window_sfml->getSize().y);
			AddMenu(msgBox);
			break;
		}
		TGUIEventHandler::events.erase(TGUIEventHandler::events.begin() + c);
	}
}
void ScreenManagement::AddMenu(MenuStructure menu)
{
	for(int c=0;c<menu.drawings_tgui.size();c++)
		this->window_tgui->add(menu.drawings_tgui.at(c));
	this->menus.push_back(menu);
}
void ScreenManagement::RemoveMenu(MenuStructure menu)
{
	int index = FindIndexOfMenu(menu);
	for(int c=0;c<this->menus.at(index).drawings_tgui.size();c++)
		this->window_tgui->remove(this->menus.at(index).drawings_tgui.at(c));
	this->menus.erase(this->menus.begin() + index);
}
int ScreenManagement::FindIndexOfMenu(MenuStructure menu)
{
	for(int c=0;c<this->menus.size();c++)
	{
		if(this->menus.at(c).drawings_sfml==menu.drawings_sfml && this->menus.at(c).drawings_tgui==menu.drawings_tgui)
			return c;
	}
	return -1;//Couldn't find it.
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