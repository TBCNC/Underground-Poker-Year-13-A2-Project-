#include "ScreenManagement.h"
#include "MessageBox.h"
#include "LoginMenu.h"
#include "MainMenu.h"
#include "Background.h"

ScreenManagement::ScreenManagement(sf::RenderWindow *window_sfml, tgui::Gui *window_tgui) {
	this->window_sfml = window_sfml;
	this->window_tgui = window_tgui;
	auto loginMenu = GameMenus::LoginScreen(this->window_sfml->getSize().x, this->window_sfml->getSize().y);
	auto background = GameMenus::BackgroundImage(this->window_sfml->getSize().x, this->window_sfml->getSize().y);
	this->menus.push_back(background);
	this->menus.push_back(loginMenu);
}
ScreenManagement::~ScreenManagement()
{
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
			if (TGUIEventHandler::events.at(c)->arguments.at(0) == "Failed to log in!") {
				MenuStructure loginMenu = GameMenus::LoginScreen(this->window_sfml->getSize().x, this->window_sfml->getSize().y);
				AddMenu(loginMenu);
				currentMenu = MenuTypes::LOG_IN_MENU;
			}
			else if (TGUIEventHandler::events.at(c)->arguments.at(0) == "Logged in successfully!") {
				MenuStructure mainMenu = GameMenus::MainMenu(this->window_sfml->getSize().x, this->window_sfml->getSize().y);
				AddMenu(mainMenu);
				currentMenu = MenuTypes::MAIN_MENU;
			}
			break;
		case TGUIEvents::MESSAGE_BOX_YES:
			RemoveMenu(TGUIEventHandler::events.at(c)->menu);
			if (TGUIEventHandler::events.at(c)->arguments.at(0) == "Are you sure you want to quit?") {
				window_sfml->close();
			}
			break;
		case TGUIEvents::MESSAGE_BOX_NO:
			RemoveMenu(TGUIEventHandler::events.at(c)->menu);
			if (TGUIEventHandler::events.at(c)->arguments.at(0) == "Are you sure you want to quit?") {
				auto mainMenu = GameMenus::MainMenu(window_sfml->getSize().x, window_sfml->getSize().y);
				AddMenu(mainMenu);
				currentMenu = MenuTypes::MAIN_MENU;
			}
			break;
		case TGUIEvents::LOG_IN:
			RemoveMenu(TGUIEventHandler::events.at(c)->menu);
			//std::cout << TGUIEventHandler::events.at(c)->arguments.at(0) << std::endl;
			UserAccount login_account(TGUIEventHandler::events.at(c)->arguments.at(0));
			if (login_account.Login(TGUIEventHandler::events.at(c)->arguments.at(1))) {
				MenuStructure msgBox = GameMenus::MessageBox("Logged in successfully!", GameMenus::MessageType::INFORMATION, GameMenus::BoxType::OK, this->window_sfml->getSize().x, this->window_sfml->getSize().y);
				AddMenu(msgBox);
			}
			else {
				MenuStructure msgBox = GameMenus::MessageBox("Failed to log in!", GameMenus::MessageType::INFORMATION, GameMenus::BoxType::OK, this->window_sfml->getSize().x, this->window_sfml->getSize().y);
				AddMenu(msgBox);
			}
			currentMenu = MenuTypes::MESSAGE_BOX;
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
void ScreenManagement::HandleSFMLEvents() {
	if (currentMenu == MenuTypes::MAIN_MENU) {
		auto boxes = GameMenus::MainMenu_GetBoxes(window_sfml->getSize().x, window_sfml->getSize().y);
		if (boxes.at(0).contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window_sfml)))) {//Play button pressed
			std::cout << "User wants to play!" << std::endl;
		}
		else if (boxes.at(1).contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window_sfml)))) {//Options button pressed
			std::cout << "User wants to access options" << std::endl;
		}
		else if (boxes.at(2).contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window_sfml)))) {//Quit button pressed
			std::cout << "User wants to quit." << std::endl;
			auto quitBox = GameMenus::MessageBox("Are you sure you want to quit?", GameMenus::MessageType::WARNING, GameMenus::BoxType::YESNO, window_sfml->getSize().x, window_sfml->getSize().y);
			RemoveMenu(this->menus.at(1));//Should always be second index.
			AddMenu(quitBox);
			currentMenu = MenuTypes::MESSAGE_BOX;
		}
	}
}
void ScreenManagement::UpdateScreen() {
	//Event polling
	sf::Event event;
	while (this->window_sfml->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			this->window_sfml->close();
		}
		this->window_tgui->handleEvent(event);
		if (event.type==sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left && TGUIEventHandler::events.size()==0) {
				HandleSFMLEvents();
			}
		}
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