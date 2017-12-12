#include "MenuStructure.h"
#include <TGUI/TGUI.hpp>
#pragma once
enum TGUIEvents : int{
	MESSAGE_BOX_OK=1,
	MESSAGE_BOX_YES=2,
	MESSAGE_BOX_NO=3,
	LOG_IN=4,
};
struct TGUIEvent
{
	MenuStructure menu;//Menu to remove
	TGUIEvents eventType;//Type of event
	std::vector<std::string> arguments;
};