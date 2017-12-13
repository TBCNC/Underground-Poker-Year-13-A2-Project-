#include "Game.h"
#include "../Network/DBConnection.h"
#include <Windows.h>

int main() {
	Game game(1280, 720);
	game.Run();
}
