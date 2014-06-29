//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "StarSystem.h"
#include "Assets.h"

float StarSystem::alphaAt(Vec2F point)
{
	return BoundBy(0.f, (1 - Distance(point, Position)/Radius)*2.f, 1.0f);
}

void StarSystem::draw(SpriteRenderer* r)
{
	r->draw(gAssets.SystemDebugSprite, Position, ForegroundStarColor);
}
