//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Platform.hpp>
#include <Springbok/Graphics.hpp>
#include "GameCode/GameWorld.h"

struct Stargazer
{
	 Stargazer();
	~Stargazer();
	int execute();
public:
	GameSurface   * Surface  = nullptr;
	InputMonitor  * Input    = nullptr;
	SpriteRenderer* Renderer = nullptr;
	
	bool IsFinished = false;
	
	GameWorld    World;
	PreciseClock Clock;
};
