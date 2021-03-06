#include "ScreenManagement.h"
#include "CreateAccountMenu.h"
#include "MessageBox.h"
#include "LoginMenu.h"
#include "MainMenu.h"
#include "Background.h"
#include "ServerList.h"
#include "PokerGame.h"
#include "ServerSetup.h"
#include "PlayMenu.h"
#include "PasswordMenu.h"

ScreenManagement::ScreenManagement(sf::RenderWindow *window_sfml, tgui::Gui *window_tgui) {
	this->client = client;
	this->window_sfml = window_sfml;
	this->window_tgui = window_tgui;
	auto background = GameMenus::BackgroundImage(this->window_sfml->getSize().x, this->window_sfml->getSize().y);
	this->menus.push_back(background);
	auto accountOptions = GameMenus::LoginScreen(this->window_sfml->getSize().x, this->window_sfml->getSize().y);
	this->menus.push_back(accountOptions);
	Client *client = new Client(1);//Using UID 1 as a test, in future it will be the user account's UID.
	this->client = client;
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
				MenuStructure mainMenu = GameMenus::MainMenu(this->window_sfml->getSize().x, this->window_sfml->getSize().y,this->user);
				AddMenu(mainMenu);
				currentMenu = MenuTypes::MAIN_MENU;
			}
			else if (TGUIEventHandler::events.at(c)->arguments.at(0) == "Please enter a valid port number!") {
				MenuStructure serverCreationMenu = GameMenus::ServerSetup(this->window_sfml->getSize().x, this->window_sfml->getSize().y);
				AddMenu(serverCreationMenu);
				currentMenu = MenuTypes::SERVER_SETUP;
			}
			else if (TGUIEventHandler::events.at(c)->arguments.at(0) == "Please fill in all fields!" || TGUIEventHandler::events.at(c)->arguments.at(0) == "Please make your password longer!" || TGUIEventHandler::events.at(c)->arguments.at(0) == "This user already exists!" || TGUIEventHandler::events.at(c)->arguments.at(0)=="You have not entered a valid email address!") {
				MenuStructure mainMenu = GameMenus::CreateAccountMenu(this->window_sfml->getSize().x, this->window_sfml->getSize().y);
				AddMenu(mainMenu);
				currentMenu = MenuTypes::CREATE_ACCOUNT_MENU;
			}
			else if (TGUIEventHandler::events.at(c)->arguments.at(0) == "Account created! You can now log in!") {
				MenuStructure logIn = GameMenus::LoginScreen(this->window_sfml->getSize().x, this->window_sfml->getSize().y);
				AddMenu(logIn);
				currentMenu = MenuTypes::LOG_IN_MENU;
			}
			else if (TGUIEventHandler::events.at(c)->arguments.at(0) == "Please select a server!" || TGUIEventHandler::events.at(c)->arguments.at(0)== "Could not connect to server!"
				|| TGUIEventHandler::events.at(c)->arguments.at(0)== "Wrong password!") {
				auto serverList = GameMenus::ServerList(this->window_sfml->getSize().x, this->window_sfml->getSize().y);
				AddMenu(serverList);
				currentMenu = MenuTypes::SERVER_LIST;
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
				auto mainMenu = GameMenus::MainMenu(window_sfml->getSize().x, window_sfml->getSize().y,this->user);
				AddMenu(mainMenu);
				currentMenu = MenuTypes::MAIN_MENU;
			}
			break;
		case TGUIEvents::LOG_IN:{
				RemoveMenu(TGUIEventHandler::events.at(c)->menu);
				//std::cout << TGUIEventHandler::events.at(c)->arguments.at(0) << std::endl;
				UserAccount login_account(TGUIEventHandler::events.at(c)->arguments.at(0),false);
				if (login_account.UserExist()) {
					if (login_account.Login(TGUIEventHandler::events.at(c)->arguments.at(1))) {
						UserAccount accountToAdd(TGUIEventHandler::events.at(c)->arguments.at(0));
						this->user = accountToAdd;
						Client *ourClient = new Client(this->user.UID);
						this->client = ourClient;
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
			case TGUIEvents::CREATE_ACCOUNT: {
				std::string username = TGUIEventHandler::events.at(c)->arguments.at(0);
				std::string password = TGUIEventHandler::events.at(c)->arguments.at(1);
				std::string email = (TGUIEventHandler::events.at(c)->arguments.at(2));
				UserAccount user(username, false);
				if (username == "" || password == "" || email == "") {
					//User not entered all details
					RemoveMenu(TGUIEventHandler::events.at(c)->menu);
					auto msgbox = GameMenus::MessageBox("Please fill in all fields!", GameMenus::MessageType::ERROR, GameMenus::BoxType::OK, this->window_sfml->getSize().x, this->window_sfml->getSize().y);
					AddMenu(msgbox);
					this->currentMenu = MenuTypes::MESSAGE_BOX;
					break;
				}
				else if (strlen(password.c_str()) < 6) {
					//password not secure enough
					RemoveMenu(TGUIEventHandler::events.at(c)->menu);
					auto msgbox = GameMenus::MessageBox("Please make your password longer!", GameMenus::MessageType::ERROR, GameMenus::BoxType::OK, this->window_sfml->getSize().x, this->window_sfml->getSize().y);
					AddMenu(msgbox);
					this->currentMenu = MenuTypes::MESSAGE_BOX;
					break;
				}
				else if (email.find("@") == std::string::npos || email.find(".com")==std::string::npos) {
					RemoveMenu(TGUIEventHandler::events.at(c)->menu);
					auto msgbox = GameMenus::MessageBox("You have not entered a valid email address!", GameMenus::MessageType::ERROR, GameMenus::BoxType::OK, this->window_sfml->getSize().x, this->window_sfml->getSize().y);
					AddMenu(msgbox);
					this->currentMenu = MenuTypes::MESSAGE_BOX;
					break;
				}
				else {
					//All good to go
					UserAccount newAccount(username, false);
					if (newAccount.CreateAccount(password,email)) {
						RemoveMenu(TGUIEventHandler::events.at(c)->menu);
						auto msgbox = GameMenus::MessageBox("Account created! You can now log in!", GameMenus::MessageType::INFORMATION, GameMenus::BoxType::OK, this->window_sfml->getSize().x, this->window_sfml->getSize().y);
						AddMenu(msgbox);
						this->currentMenu = MenuTypes::MESSAGE_BOX;
						break;
					}
					else {
						RemoveMenu(TGUIEventHandler::events.at(c)->menu);
						auto msgbox = GameMenus::MessageBox("This user already exists!", GameMenus::MessageType::ERROR, GameMenus::BoxType::OK, this->window_sfml->getSize().x, this->window_sfml->getSize().y);
						AddMenu(msgbox);
						this->currentMenu = MenuTypes::MESSAGE_BOX;
						break;
					}
				}
				break;
			}
			case TGUIEvents::CHANGE_TO_CREATE_MENU: {
				RemoveMenu(TGUIEventHandler::events.at(c)->menu);
				auto accountCreationMenu = GameMenus::CreateAccountMenu(this->window_sfml->getSize().x, this->window_sfml->getSize().y);
				AddMenu(accountCreationMenu);
				this->currentMenu = MenuTypes::CREATE_ACCOUNT_MENU;
				break;
			}
			case TGUIEvents::CREATE_SERVER: {
				std::string serverName = TGUIEventHandler::events.at(c)->arguments.at(0);
				std::string serverPasswowrd = TGUIEventHandler::events.at(c)->arguments.at(1);
				std::string portNum = (TGUIEventHandler::events.at(c)->arguments.at(2));
				if (portNum.find_first_not_of("0123456789") == std::string::npos) {
					//This is a number
					int portNum_int = std::stoi(portNum);
					Server *server = new Server(serverName, portNum_int, false, serverPasswowrd);
					this->server = server;
					RemoveMenu(TGUIEventHandler::events.at(c)->menu);
					this->chatHistory.clear();
					this->currentPlayers.clear();
					this->pokerBoundaries.clear();
					this->userCards.clear();
					this->tableCards.clear();
					auto pokerGame = GameMenus::PokerGame(this->window_sfml->getSize().x, this->window_sfml->getSize().y, this->usersTurn, &this->pokerBoundaries);
					AddMenu(pokerGame);
					this->currentMenu = MenuTypes::POKER_GAME;
					std::thread serverThread(&Server::Start,this->server);
					this->client->ConnectToServer("127.0.0.1", portNum_int);
					std::thread clientThread(&Client::ListenForData,this->client);
					serverThread.detach();
					sleep(sf::milliseconds(25));
					clientThread.detach();
				}
				else {
					RemoveMenu(TGUIEventHandler::events.at(c)->menu);
					auto msgbox = GameMenus::MessageBox("Please enter a valid port number!", GameMenus::MessageType::ERROR, GameMenus::BoxType::OK, this->window_sfml->getSize().x, this->window_sfml->getSize().y);
					AddMenu(msgbox);
					this->currentMenu = MenuTypes::MESSAGE_BOX;
					break;
				}
				break;
			}
			case TGUIEvents::JOIN_SERVER:
				if (TGUIEventHandler::events.at(c)->arguments.size() != 0) {
					std::string ip = TGUIEventHandler::events.at(c)->arguments.at(0);
					int port = std::stoi(TGUIEventHandler::events.at(c)->arguments.at(1));
					std::string password = TGUIEventHandler::events.at(c)->arguments.at(2);
					if (password == "") {
						if (this->client->ConnectToServer(ip, port)) {
							//Load the poker table
							RemoveMenu(TGUIEventHandler::events.at(c)->menu);
							auto pokerGame = GameMenus::PokerGame(this->window_sfml->getSize().x, this->window_sfml->getSize().y, false,&this->pokerBoundaries);
							this->currentMenu = MenuTypes::POKER_GAME;
							AddMenu(pokerGame);
							std::thread clientThread(&Client::ListenForData, this->client);
							clientThread.detach();
						}
						else {
							RemoveMenu(TGUIEventHandler::events.at(c)->menu);
							auto msgBox = GameMenus::MessageBox("Could not connect to server!", GameMenus::MessageType::ERROR, GameMenus::BoxType::OK, this->window_sfml->getSize().x, this->window_sfml->getSize().y);
							AddMenu(msgBox);
						}
					}
					else {
						//Spawn password menu
						this->latestIP = ip;
						this->latestPort = port;
						RemoveMenu(TGUIEventHandler::events.at(c)->menu);
						auto passwordField = GameMenus::PasswordBox(this->window_sfml->getSize().x, this->window_sfml->getSize().y, password);
						AddMenu(passwordField);
						this->currentMenu = MenuTypes::PASSWORD_MENU;
					}
				}
				else {
					RemoveMenu(TGUIEventHandler::events.at(c)->menu);
					auto msgBox = GameMenus::MessageBox("Please select a server!", GameMenus::MessageType::ERROR, GameMenus::BoxType::OK, this->window_sfml->getSize().x, this->window_sfml->getSize().y);
					AddMenu(msgBox);
					this->currentMenu = MenuTypes::MESSAGE_BOX;
				}
				break;
			case TGUIEvents::PASSWORD_ENTERED: {
				if (TGUIEventHandler::events.at(c)->arguments.at(0)=="1") {
					//Join the server
					if (this->client->ConnectToServer(this->latestIP, this->latestPort)) {
						RemoveMenu(TGUIEventHandler::events.at(c)->menu);
						auto pokerGame = GameMenus::PokerGame(this->window_sfml->getSize().x, this->window_sfml->getSize().y, false, &this->pokerBoundaries);
						this->currentMenu = MenuTypes::POKER_GAME;
						AddMenu(pokerGame);
						std::thread clientThread(&Client::ListenForData, this->client);
						clientThread.detach();
						break;
					}
				}
				else {
					RemoveMenu(TGUIEventHandler::events.at(c)->menu);
					auto msgBox = GameMenus::MessageBox("Wrong password!", GameMenus::MessageType::ERROR, GameMenus::BoxType::OK, this->window_sfml->getSize().x, this->window_sfml->getSize().y);
					AddMenu(msgBox);
					this->currentMenu = MenuTypes::MESSAGE_BOX;
					break;
				}
				break;
			}
			case TGUIEvents::CHANGE_TO_SERVER_LIST: {
				RemoveMenu(TGUIEventHandler::events.at(c)->menu);
				auto serverList = GameMenus::ServerList(this->window_sfml->getSize().x, this->window_sfml->getSize().y);
				AddMenu(serverList);
				this->currentMenu = MenuTypes::SERVER_LIST;
				break;
			}
			case TGUIEvents::CHANGE_TO_SERVER_SETUP: {
				RemoveMenu(TGUIEventHandler::events.at(c)->menu);
				auto serverSetup = GameMenus::ServerSetup(this->window_sfml->getSize().x, this->window_sfml->getSize().y);
				AddMenu(serverSetup);
				this->currentMenu = MenuTypes::SERVER_SETUP;
				break;
			}
			case TGUIEvents::CHANGE_TO_PLAY_MENU: {
				RemoveMenu(TGUIEventHandler::events.at(c)->menu);
				auto playMenu = GameMenus::PlayMenu(this->window_sfml->getSize().x, this->window_sfml->getSize().y);
				AddMenu(playMenu);
				this->currentMenu = MenuTypes::PLAY_CHOICE;
				break;
			}
			case TGUIEvents::CHANGE_TO_MAIN_MENU: {
				RemoveMenu(TGUIEventHandler::events.at(c)->menu);
				auto playMenu = GameMenus::MainMenu(this->window_sfml->getSize().x, this->window_sfml->getSize().y,this->user);
				AddMenu(playMenu);
				this->currentMenu = MenuTypes::MAIN_MENU;
				break;
			}
			case TGUIEvents::SLIDER_CHANGED: {
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
			auto newMenu = GameMenus::PokerGame(this->window_sfml->getSize().x, this->window_sfml->getSize().y, this->usersTurn, &this->pokerBoundaries, this->chatHistory,this->currentPlayers,this->userCards,this->tableCards);
			AddMenu(newMenu);
			break;
		}
		case SERVER_MESSAGE: {
			this->chatHistory.push_back(this->client->events.at(c).payload);
			RemoveMenu(this->menus.at(1));
			auto newMenu = GameMenus::PokerGame(this->window_sfml->getSize().x, this->window_sfml->getSize().y, this->usersTurn, &this->pokerBoundaries, this->chatHistory, this->currentPlayers, this->userCards,this->tableCards);
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
				Player *newPlayer = new Player(UserAccount(std::stoi(uids.at(i)), true));
				players.push_back(newPlayer);
			}
			this->currentPlayers = players;
			RemoveMenu(this->menus.at(1));
			auto newMenu = GameMenus::PokerGame(this->window_sfml->getSize().x, this->window_sfml->getSize().y, this->usersTurn, &this->pokerBoundaries, this->chatHistory, this->currentPlayers,this->userCards,this->tableCards);
			AddMenu(newMenu);
			break;
		}
		case HAND_INFORMATION: {
			//Suit then val
			std::stringstream stream(this->client->events.at(c).payload);
			std::string item;
			std::vector<std::string> cards;
			while (getline(stream, item, ',')) {
				cards.push_back(item);
			}
			this->userCards.clear();
			for (int c = 0; c < cards.size(); c++) {
				Card newCard;
				newCard.card_suit = (Suit)(cards.at(c)[0]-'0');
				int cardval = std::stoi(cards.at(c).substr(1, strlen(cards.at(c).c_str())-1));
				std::cout << cardval << std::endl;
				newCard.card_value = (Value)cardval;
				std::cout << "Added card of suit " << newCard.card_suit << " and value " << newCard.card_value << std::endl;
				this->userCards.push_back(newCard);
			}
			RemoveMenu(this->menus.at(1));
			auto newMenu = GameMenus::PokerGame(this->window_sfml->getSize().x, this->window_sfml->getSize().y, this->usersTurn, &this->pokerBoundaries, this->chatHistory, this->currentPlayers, this->userCards,this->tableCards);
			AddMenu(newMenu);
			break;
		}
		case MOVE_REQUIRED: {
			this->chatHistory.push_back("It's your turn!");
			this->usersTurn = true;
			RemoveMenu(this->menus.at(1));
			auto newMenu = GameMenus::PokerGame(this->window_sfml->getSize().x, this->window_sfml->getSize().y, this->usersTurn, &this->pokerBoundaries, this->chatHistory, this->currentPlayers, this->userCards,this->tableCards);
			AddMenu(newMenu);
			break;
		}
		case MOVE_FOLD: {
			std::cout << "A player has folded." << std::endl;
			for (int i = 0; i < this->currentPlayers.size(); i++) {
				if (this->currentPlayers.at(i)->user.UID == std::stoi(this->client->events.at(c).payload)) {
					this->currentPlayers.at(i)->playing = false;
					break;
				}
			}
			RemoveMenu(this->menus.at(1));
			auto newMenu = GameMenus::PokerGame(this->window_sfml->getSize().x, this->window_sfml->getSize().y, this->usersTurn, &this->pokerBoundaries, this->chatHistory, this->currentPlayers, this->userCards,this->tableCards,this->totalJackpot);
			AddMenu(newMenu);
			break;
		}
		case MOVE_CALL: {
			std::cout << "A player has called." << std::endl;
			std::stringstream stream(this->client->events.at(c).payload);
			std::string item;
			std::vector<std::string> data;
			while (getline(stream, item, ',')) {
				data.push_back(item);
			}
			int uid = std::stoi(data.at(0));
			int points = std::stoi(data.at(1));
			for (int i = 0; i < this->currentPlayers.size();i++) {
				if (this->currentPlayers.at(i)->user.UID == uid) {
					this->currentPlayers.at(i)->points -= points;
					this->totalJackpot += points;
					break;
				}
			}
			RemoveMenu(this->menus.at(1));
			auto newMenu = GameMenus::PokerGame(this->window_sfml->getSize().x, this->window_sfml->getSize().y, this->usersTurn, &this->pokerBoundaries, this->chatHistory, this->currentPlayers, this->userCards, this->tableCards,this->totalJackpot);
			AddMenu(newMenu);
			break;
		}
		case TABLE_CARDS: {
			std::cout << "Got all the table cards " << this->client->events.at(c).payload << std::endl;
			std::stringstream stream(this->client->events.at(c).payload);
			std::string item;
			std::vector<std::string> cards;
			while (getline(stream, item, ',')) {
				cards.push_back(item);
			}
			this->tableCards.clear();
			for (int c = 0; c < cards.size(); c++) {
				Card newCard;
				newCard.card_suit = (Suit)(cards.at(c)[0] - '0');
				int cardval = std::stoi(cards.at(c).substr(1, strlen(cards.at(c).c_str()) - 1));
				std::cout << cardval << std::endl;
				newCard.card_value = (Value)cardval;
				std::cout << "Added card of suit " << newCard.card_suit << " and value " << newCard.card_value << std::endl;
				this->tableCards.push_back(newCard);
			}
			RemoveMenu(this->menus.at(1));
			auto newMenu = GameMenus::PokerGame(this->window_sfml->getSize().x, this->window_sfml->getSize().y, this->usersTurn, &this->pokerBoundaries, this->chatHistory, this->currentPlayers, this->userCards,this->tableCards,this->totalJackpot);
			AddMenu(newMenu);
			break;
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
			//auto serverList = GameMenus::ServerList(window_sfml->getSize().x, window_sfml->getSize().y);
			auto playMenu = GameMenus::PlayMenu(this->window_sfml->getSize().x, this->window_sfml->getSize().y);
			RemoveMenu(this->menus.at(1));
			AddMenu(playMenu);
			currentMenu = MenuTypes::PLAY_CHOICE;
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
	}
	else{
		if (this->usersTurn) {
			if (this->pokerBoundaries.at(0).contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window_sfml)))) {
				std::cout << "User wants to fold!" << std::endl;
				this->usersTurn = false;
				this->client->SendPacketToServer(PacketType::MOVE_FOLD, "");
				RemoveMenu(this->menus.at(1));
				auto newMenu = GameMenus::PokerGame(this->window_sfml->getSize().x, this->window_sfml->getSize().y, this->usersTurn, &this->pokerBoundaries, this->chatHistory, this->currentPlayers, this->userCards,this->tableCards,this->totalJackpot);
				AddMenu(newMenu);
			}
			else if (this->pokerBoundaries.at(1).contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window_sfml)))) {
				std::cout << "User wants to call!" << std::endl;
				this->usersTurn = false;
				this->client->SendPacketToServer(PacketType::MOVE_CALL, std::to_string(GameMenus::pointSlider->getValue()));
				RemoveMenu(this->menus.at(1));
				auto newMenu = GameMenus::PokerGame(this->window_sfml->getSize().x, this->window_sfml->getSize().y, this->usersTurn, &this->pokerBoundaries, this->chatHistory, this->currentPlayers, this->userCards,this->tableCards,this->totalJackpot);
				AddMenu(newMenu);
			}
			else if (this->pokerBoundaries.at(2).contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window_sfml)))) {
				std::cout << "User wants to raise!" << std::endl;
				this->usersTurn = false;
				this->client->SendPacketToServer(PacketType::MOVE_RAISE, std::to_string(GameMenus::pointSlider->getValue()));
				RemoveMenu(this->menus.at(1));
				auto newMenu = GameMenus::PokerGame(this->window_sfml->getSize().x, this->window_sfml->getSize().y, this->usersTurn, &this->pokerBoundaries, this->chatHistory, this->currentPlayers, this->userCards,this->tableCards,this->totalJackpot);
				AddMenu(newMenu);
			}
		}
	}
}
void ScreenManagement::UpdateScreen() {
	//Event polling
	try {
		this->mouseOn = false;
		sf::Event event;
		if(this->client!=nullptr)
			if (this->client->events.size() > 0)
				this->HandleClientEvents();

		if (TGUIEventHandler::events.size() > 0)
			this->HandleTGUIEvents();

		while (this->window_sfml->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				this->window_sfml->close();
			}
			this->window_tgui->handleEvent(event);
			if (event.type == sf::Event::MouseButtonPressed) {
				this->mouseOn = true;
				if (event.mouseButton.button == sf::Mouse::Left && TGUIEventHandler::events.size() == 0) {
					HandleSFMLEvents();
				}
			}
		}
		//Graphical drawing
		this->window_sfml->clear();
		this->DrawSFML();
		this->window_tgui->draw();
		this->window_sfml->display();
	}
	catch (...) {
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