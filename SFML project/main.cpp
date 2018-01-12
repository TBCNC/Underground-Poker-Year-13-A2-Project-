#include "Game.h"
#include "../Network/DBConnection.h"
#include <iostream>
//#include "../Network/ELORanker.h"
#include <Windows.h>

int main() {
	Game game(1280, 720);
	game.Run();
}
 