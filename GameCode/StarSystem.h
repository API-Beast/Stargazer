//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "GameObject.h"

struct StarSystem : public StaticObject
{
	void draw(SpriteRenderer* r);
	float alphaAt(Vec2F point);
	
	// Vec2F Position from StaticObject
	float Radius;
	float CoreSize = 200;
	
	Vec3F  CoreColor = Colors::White;
	
	Vec4F BackgroundStarColor  = Colors::Transparent;
	Vec4F BackgroundFogColorsA = Colors::Transparent;
	Vec4F BackgroundFogColorsB = Colors::Transparent;
	Vec4F ForegroundStarColor  = Colors::Transparent;
};

struct Planet : public StaticObject
{
};