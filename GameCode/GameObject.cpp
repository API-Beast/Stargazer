//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "GameObject.h"
#include "Assets.h"
#include <Springbok/Graphics.hpp>

void Serializable::deserialize(const ValueTree& obj)
{

}

void GameObject::drawDebug(SpriteRenderer& r)
{
	r.draw(LineShape::Arrow(Acceleration, gAssets.Arrow), Position, Int2Color(0xffffa22f));
	r.draw(LineShape::Arrow(Speed,        gAssets.Arrow), Position, Int2Color(0xff5fcde4));
	for(Vec2F force : VecForces)
		r.draw(LineShape::Arrow(force, gAssets.Arrow), Position, Int2Color(0xdff77bba));
	
	Transform2D t = Position2D(Position) + Rotate2D(Rotation);
	r.draw(LineShape::TurnIndicator(Angle::FromTurn(RotationSpeed), 50, gAssets.Arrow), t);
	for(Angle angle : RotForces)
		r.draw(LineShape::TurnIndicator(angle, 50, gAssets.Arrow), t, Int2Color(0xfffbf236));
}

void GameObject::update(GameState* state, float dt)
{
	VecForces.clear();
	RotForces.clear();
}

void GameObject::applyRotForce(Angle force, float dt)
{
	Rotation += force * dt;
	RotForces.pushBack(force);
}

void GameObject::applyVecForce(Vec2F force, float dt)
{
	Speed += force * dt;
	VecForces.pushBack(force);
}
