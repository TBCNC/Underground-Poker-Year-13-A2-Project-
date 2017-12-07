#include "Login.h"

Login::Login(sf::String username, sf::String password) {
	this->username = username;
	this->password = password;
}
void Login::CheckCredentials() {
	//Check if there are any illgeal characters, invalid lengths, etc.
}