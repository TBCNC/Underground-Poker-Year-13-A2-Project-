#include "TGUIEvents.h"
#include <vector>
#pragma once
class TGUIEventHandler
{
public:
	static std::vector<TGUIEvent*> events;
};