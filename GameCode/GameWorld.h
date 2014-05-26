//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once
#include <Springbok/Graphics/SpriteRenderer.h>

// Seperated from GameWorld for easy copying/saving/loading/manipulating/networking etc.
// At best all components of GameState should be Plain-Old-Data so that you could theoretically just write the whole thing into a stream byte by byte
// Things that don't influence gameplay (Graphics, Sounds) shouldn't be stored here either
struct GameState
{
};

// The idea is that GameWorld only contains the Gameplay itself, with all platform or client details handled by the Game class. 
struct GameWorld
{
public:
	void update(float deltaTime);
	void draw(SpriteRenderer* r);
public:
	GameState State;
};
