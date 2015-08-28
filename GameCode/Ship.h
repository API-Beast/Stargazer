//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "GameObject.h"
#include <Springbok/Graphics/Image.h>

struct ShipDefinition : public Serializable
{
	std::string Identifier;
	
	Image Sprite;
	Image SpriteOverlay;
	
	Image Picture;
	Image PictureOverlay;
	
	float EngineAccleration;
	
	void loadFromPath(const std::string& path);
	virtual void deserialize(const ValueTree& obj);
};

struct Ship : public GameObject
{
	Ship(ShipDefinition* def);
	virtual void drawSprite(SpriteRenderer& r);
	virtual void update(GameState* state, float dt);
	virtual void applyRotForce(Angle force, float dt);
	
	ObjPtr<ShipDefinition> Definition;
	int Faction;
	Angle DesiredDirection;
};