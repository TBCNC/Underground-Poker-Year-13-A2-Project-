#include "TGUIEventHandler.h"

std::vector<TGUIEvent*> TGUIEventHandler::events;
TGUIEventHandler::~TGUIEventHandler() {//Prevents memory leaks
	for (int c = 0; c < this->events.size(); c++) {
		for (int i = 0; i < this->events.at(c)->menu.drawings_sfml.size(); i++) {
			delete(this->events.at(c)->menu.drawings_sfml.at(i));
		}
		delete(&this->events.at(c)->menu);
		delete(this->events.at(c));
	}
	this->events.clear();
}