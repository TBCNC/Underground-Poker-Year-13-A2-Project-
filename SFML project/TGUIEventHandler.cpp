#include "TGUIEventHandler.h"

std::vector<TGUIEvent*> TGUIEventHandler::events;
TGUIEventHandler::~TGUIEventHandler() {//Prevents memory leaks
	for (int c = 0; c < this->events.size(); c++) {
		delete(&this->events.at(c)->menu);
		delete(this->events.at(c));
	}
	this->events.clear();
}