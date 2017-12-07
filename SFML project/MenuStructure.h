#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#pragma once
struct MenuStructure{
	std::vector <sf::Drawable*> drawings_sfml;
	std::vector <tgui::Widget::Ptr> drawings_tgui;
};
