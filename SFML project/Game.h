#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <TGUI/TGUI.hpp>
#include "ScreenManagement.h"
class Game {
public:
	Game(int width, int height, bool AA = true);
	void Run();
	int width;
	int height;
	bool AA;
private:
	sf::RenderWindow *window;
	tgui::Gui *gui;
};