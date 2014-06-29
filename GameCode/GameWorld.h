//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Graphics/SpriteRenderer.h>
#include <Springbok/Containers/List.h>

#include "GameObject.h"
#include "StarSystem.h"
#include "Ship.h"
#include "../LibCode/Controls.h"

template<typename T>
using DefMap = Map<T, std::string, &T::Identifier>;

class InputMonitor;

struct GameDefinitions
{
	DefMap<ShipDefinition> Ships;
};

struct PlayerControls
{
	DirectionControl Rotation;
};

// Seperated from GameWorld for easy copying/saving/loading/manipulating/networking etc.
// At best all components of GameState should be Plain-Old-Data so that you could theoretically just write the whole thing into a stream byte by byte
// Things that don't influence gameplay (Graphics, Sounds) shouldn't be stored here either
struct GameState
{
	List<GameObject*> Objects;
	List<Ship*>       Ships;
	ObjPtr<Ship>      Player;
	List<StarSystem>  Systems;
	
	void update(float deltaTime);
	void applyPhysics(GameObject* obj, float dt);
	
	struct
	{
		float AirDrag = 0.001f;
		float AirFlow = 0.02f;
	} Params;
};

// The idea is that GameWorld only contains the Gameplay itself, with all platform or client details handled by the Game class. 
struct GameWorld
{
public:
	void init();
	void setupDisplay(GameSurface* surface);
	void setupInput(InputMonitor* input);
	void update(float deltaTime, InputMonitor* Input);
	void draw(SpriteRenderer* r);
	void loadDefinitions(const std::string& folder);
public:
	GameState       State;
	GameDefinitions Definitions;
	Framebuffer*    HDRTarget = nullptr;
	PlayerControls  Controls;
};
