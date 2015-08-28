//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Ship.h"

#include "Assets.h"

#include <Springbok/Utils.hpp>
#include <Springbok/Serialization.hpp>
#include <Springbok/Graphics.hpp>

void ShipDefinition::deserialize(const ValueTree& obj)
{
	Sprite            = Image(obj.value("Sprite"));
	SpriteOverlay     = Image(obj.value("SpriteOverlay"));
	Picture           = Image(obj.value("Picture"));
	PictureOverlay    = Image(obj.value("PictureOverlay"));
	EngineAccleration = std::stof(obj.value("EngineAccleration"));
	Identifier        = obj.value("Identifier");
}

void ShipDefinition::loadFromPath(const std::string& path)
{
	ValueTree root = LoadXINI(ResourceManager::GetInstance()->getPath(path));
	deserialize(root);
}

Ship::Ship(ShipDefinition* def)
{
	Definition = def;
}

void Ship::drawSprite(SpriteRenderer& r)
{
	Transform2D t = Position2D(Position) + Rotate2D(Rotation);
	Vec4F c = RGB(1.0, 1.0, 1.0, 1.0);
	//if(Acceleration.isNull())
	//	c = Colors::Blue;
	r.draw(Definition->Sprite, t, c);
}

void Ship::update(GameState* state, float dt)
{
	GameObject::update(state, dt);
	bool acclerating = true;
	Angle direction(Speed);
	if(direction != DesiredDirection)
	{
		//Vec2F steer = direction - DesiredDirection;
		if(Rotation.toDirection().dot(DesiredDirection.toDirection()) < 0.50f)
			acclerating = false;
		
		Rotation = Approach(Rotation, DesiredDirection, Angle::FromTurn(dt));
	}
	
	if(acclerating)
		Acceleration = Rotation.toDirection() * Definition->EngineAccleration;
	else
		Acceleration = 0;
}

void Ship::applyRotForce(Angle force, float dt)
{
	GameObject::applyRotForce(force, dt);
	DesiredDirection += force*dt;
}

