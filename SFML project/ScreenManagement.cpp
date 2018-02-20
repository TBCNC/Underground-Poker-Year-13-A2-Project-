#include "ScreenManagement.h"
#include "MessageBox.h"
#include "LoginMenu.h"
#include "MainMenu.h"
#include "Background.h"
#include "ServerList.h"
#include "PokerGame.h"
#include "ServerSetup.h"

ScreenManagement::ScreenManagement(sf::RenderWindow *window_sfml, tgui::Gui *window_tgui) {


	this->client = client;
	this->window_sfml = window_sfml;
	this->window_tgui = window_tgui;
	auto background = GameMenus::BackgroundImage(this->window_sfml->getSize().x, this->window_sfml->getSize().y);
	this->menus.push_back(background);
	//auto loginMenu = GameMenus::LoginScreen(this->window_sfml->getSize().x, this->window_sfml->getSize().y);
	//this->menus.push_back(loginMenu);
	
	int uid;
	std::cout << "Enter UID:";
	std::cin >> uid;
	Client *client = new Client(uid);
	this->client = client;
	std::thread clientThread(&Client::ConnectToServer,this->client,"192.168.0.15",666);
	clientThread.detach();
	
	/*UserAccount *userAccount1 = new UserAccount(1, true);
	UserAccount *userAccount2 = new UserAccount(2, true);
	UserAccount *userAccount3 = new UserAccount(3, true);*/

	auto poker = GameMenus::PokerGame(this->window_sfml->getSize().x, this->window_sfml->getSize().y, this->usersTurn, &this->pokerBoundaries);
	this->menus.push_back(poker);
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
		switch (TGUIEventHandler::events.at(c)->eventType)
		{
		case TGUIEvents::MESSAGE_BOX_OK:
			RemoveMenu(TGUIEventHandler::events.at(c)->menu);
			if (TGUIEventHandler::events.at(c)->arguments.at(0) == "Failed to log in!" || TGUIEventHandler::events.at(c)->arguments.at(0) == "This user does not exist!") {
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
		case TGUIEvents::LOG_IN:{
				RemoveMenu(TGUIEventHandler::events.at(c)->menu);
				//std::cout << TGUIEventHandler::events.at(c)->arguments.at(0) << std::endl;
				UserAccount login_account(TGUIEventHandler::events.at(c)->arguments.at(0));
				if (login_account.UserExist()) {
					if (login_account.Login(TGUIEventHandler::events.at(c)->arguments.at(1))) {
						this->user = login_account;
						MenuStructure msgBox = GameMenus::MessageBox("Logged in successfully!", GameMenus::MessageType::INFORMATION, GameMenus::BoxType::OK, this->window_sfml->getSize().x, this->window_sfml->getSize().y);
						AddMenu(msgBox);
					}
					else {
						MenuStructure msgBox = GameMenus::MessageBox("Failed to log in!", GameMenus::MessageType::INFORMATION, GameMenus::BoxType::OK, this->window_sfml->getSize().x, this->window_sfml->getSize().y);
						AddMenu(msgBox);
					}
				}
				else {
					MenuStructure msgBox = GameMenus::MessageBox("This user does not exist!", GameMenus::MessageType::ERROR, GameMenus::BoxType::OK, this->window_sfml->getSize().x, this->window_sfml->getSize().y);
					AddMenu(msgBox);
				}
				currentMenu = MenuTypes::MESSAGE_BOX;
				break;
			}
			case TGUIEvents::SEND_CHAT_MESSAGE: {
				std::string chatMsg = TGUIEventHandler::events.at(c)->arguments.at(0);
				this->client->SendPacketToServer(PacketType::CHAT_MESSAGE, chatMsg);
				break;
			}
		}
		
		TGUIEventHandler::events.erase(TGUIEventHandler::events.begin() + c);
	}
}
void ScreenManagement::HandleClientEvents() {//Handling what is received
	for (int c = 0; c < this->client->events.size(); c++) {
		switch (this->client->events.at(c).type) {
		case CHAT_MESSAGE: {
			this->chatHistory.push_back(this->client->events.at(c).payload);
			RemoveMenu(this->menus.at(1));
			auto newMenu = GameMenus::PokerGame(this->window_sfml->getSize().x, this->window_sfml->getSize().y, this->usersTurn, &this->pokerBoundaries, this->chatHistory,this->currentPlayers);
			AddMenu(newMenu);
			break;
		}
		case ALL_PLAYERS: {
			std::cout << "A player has connected." << std::endl;
			std::stringstream stream(this->client->events.at(c).payload);
			std::string item;
			std::vector<std::string> uids;
			while (getline(stream, item, ',')) {
				uids.push_back(item);
			}
			std::vector<Player*> players;
			for (int i = 0; i < uids.size(); i++) {
				std::cout << "Adding UID " << uids.at(i) << std::endl;
				Player *newPlayer = new Player(UserAccount(std::stoi(uids.at(i)),true));
				players.push_back(newPlayer);
			}
			this->currentPlayers = players;
			RemoveMenu(this->menus.at(1));
			auto newMenu = GameMenus::PokerGame(this->window_sfml->getSize().x, this->window_sfml->getSize().y, this->usersTurn, &this->pokerBoundaries, this->chatHistory, this->currentPlayers);
			AddMenu(newMenu);
		}
		}
		this->client->events.erase(this->client->events.begin()+c);
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
			auto serverList = GameMenus::ServerList(window_sfml->getSize().x, window_sfml->getSize().y);
			RemoveMenu(this->menus.at(1));
			AddMenu(serverList);
			currentMenu = MenuTypes::SERVER_LIST;
		}
		else if (boxes.at(1).contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window_sfml)))) {//Options button pressed
			std::cout << "User wants to access options" << std::endl;
		}
		else if (boxes.at(2).contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window_sfml)))) {//Quit button pressed
			std::cout << "User wants to quit." << std::endl;
			auto quitBox = GameMenus::MessageBox("Are you sure you want to quit?", GameMenus::MessageType::WARNING, GameMenus::BoxType::YESNO, window_sfml->getSize().x, window_sfml->getSize().y);
			RemoveMenu(this->menus.at(1));
			AddMenu(quitBox);
			currentMenu = MenuTypes::MESSAGE_BOX;
		}
	}else if(currentMenu == MenuTypes::POKER_GAME) {
		//auto game = this->menus.at(1);
	}
}
void ScreenManagement::UpdateScreen() {
	//Event polling
	try {
		sf::Event event;
		while (this->window_sfml->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				this->window_sfml->close();
			}
			this->window_tgui->handleEvent(event);
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left && TGUIEventHandler::events.size() == 0) {
					HandleSFMLEvents();
				}
			}
			if (TGUIEventHandler::events.size() > 0)
				this->HandleTGUIEvents();
			if (this->client->events.size() > 0)
				this->HandleClientEvents();
		}
		//Graphical drawing
		this->window_sfml->clear();
		this->DrawSFML();
		this->window_tgui->draw();
		this->window_sfml->display();
	}
	catch (...) {
		std::cout << "Oh fuck" << std::endl;
	}
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