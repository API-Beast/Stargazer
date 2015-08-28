//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Foundation.hpp>
#include <Springbok/Serialization.hpp>
#include "../LibCode/BoundingShapes.h"
#include "../LibCode/List.h"

#include <string>

class GameState;
class SpriteRenderer;

struct StaticObject
{
	Vec2F Position = 0;

	Vec2F BoundsOffset = 0;
	BoundingRect Bounds = BoundingRect{0, 16}; // Position updated every frame
	virtual void updateBounds(){ Bounds.setCenter(Position - BoundsOffset); };
};

struct PhysicsObject : public StaticObject
{
	Vec2F Speed = 0;
	Vec2F Acceleration = 0;
	
	Angle Rotation = 0_turn;
	float RotationSpeed = 0;
	
	float Drag = 1.f;
	float Flow = 1.f;
};

struct GameObject : public PhysicsObject
{
	virtual void drawDebug  (SpriteRenderer& r);
	virtual void drawSprite (SpriteRenderer& r){};
	virtual void drawPicture(SpriteRenderer& r, float sizeMult){};
	
	virtual void update(GameState* state, float dt);
	virtual void onCollision(GameObject* other, GameState* state){};
	
	virtual void applyVecForce(Vec2F force, float dt);
	virtual void applyRotForce(Angle force, float dt);
	
	List<Vec2F> VecForces;
	List<Angle> RotForces;
};

struct Serializable
{
	virtual void deserialize(const ValueTree& obj);
};
