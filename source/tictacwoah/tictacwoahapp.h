#ifndef TICTACWOAHAPP_H
#define TICTACWOAHAPP_H

#include <app\application.h>
#include <view\human\humanview.h>
#include <app\physics\boxcollider.h>
#include <view\render\ui\textbox.h>

#include "tictacview.h"

// include to use Spriter animations
#include <spriterengine/spriterengine.h>
#include <spriterengine/global/settings.h>
#include "logic\tictaclogic.h"

// Creating this so stuff will work
class TicTacWoahApp : public Application
{
public:
	virtual bool CreateLogicAndViews();
	virtual const char* Name();

	TicTacLogic logic;
};

#endif
