#include "MenuStructure.h"
#include <TGUI/TGUI.hpp>
#pragma once
enum TGUIEvents : int{
	MESSAGE_BOX_OK=1,
	MESSAGE_BOX_YES=2,
	MESSAGE_BOX_NO=3,
	LOG_IN=4,
	SEND_CHAT_MESSAGE=5,
	SLIDER_CHANGED=6,
	CREATE_SERVER=7,
	CREATE_ACCOUNT=8,
	CHANGE_TO_CREATE_MENU=9,
	CHANGE_TO_SERVER_LIST=10,
	CHANGE_TO_SERVER_SETUP=11,
	CHANGE_TO_PLAY_MENU=12,
	CHANGE_TO_MAIN_MENU=13,
};
struct TGUIEvent
{
	MenuStructure menu;//Menu to remove
	TGUIEvents eventType;//Type of event
	std::vector<std::string> arguments;
};