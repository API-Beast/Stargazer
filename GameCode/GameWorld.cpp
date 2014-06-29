//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "GameWorld.h"
#include "Assets.h"
#include <Springbok/Platform.hpp>

void GameWorld::init()
{
	gAssets.init();
	ShipDefinition playerShip;
	playerShip.loadFromPath("Definitions/PlayerShip.xini");
	State.Player = new Ship(&Definitions.Ships.insert(playerShip));
	State.Objects.pushBack(State.Player);
	State.Ships.pushBack(State.Player);
	
	StarSystem A;
	A.Position.Y = 2500;
	A.Radius = 2000;
	A.BackgroundFogColorsA = RGB(0, 0.55f, 0.15f, 0.75f);
	State.Systems.pushBack(A);
	
	StarSystem B;
	B.Position.Y = -2500;
	B.Radius = 2000;
	B.BackgroundFogColorsA = RGB(0.25f, 0.0f, 0.15f, 0.75f);
	B.BackgroundFogColorsB = RGB(0.75f, 0.3f, 0.1f, 0.75f);
	B.ForegroundStarColor  = RGB(2.25f, 1.75f, 0.5f, 1.0f);
	State.Systems.pushBack(B);
}

void GameWorld::setupDisplay(GameSurface* surface)
{
	delete HDRTarget;
	HDRTarget = new Framebuffer(surface->size().X, surface->size().Y);
}

void GameWorld::setupInput(InputMonitor* input)
{
	Controls.Rotation = DirectionControl::FourButton(input, "W", "S", "A", "D");
}

namespace
{
	template<typename T>
	T AlphaBlend(T dst, T src, float srcAlpha)
	{
		return dst * (1 - srcAlpha) + src * srcAlpha;
	};
};

void GameWorld::draw(SpriteRenderer* r)
{
	RenderTarget* window = r->Context.renderTarget();
	
	if(window->size() != HDRTarget->size())
	{
		delete HDRTarget;
		HDRTarget = new Framebuffer(window->size().X, window->size().Y, 16);
	}
	
	r->Context.setRenderTarget(HDRTarget);
	r->Context.setShader(ShaderProgram::GetDefaultShader());
	
	ColorRGBA BackgroundStarColor  = Colors::Dawn::Turquoise[1];
	ColorRGBA BackgroundFogColorsA = ColorRGBA(Colors::Dawn::Charcoal[2], 0.5f);
	ColorRGBA BackgroundFogColorsB = ColorRGBA(Colors::Dawn::Purple[1], 0.5f);
	ColorRGBA ForegroundStarColor  = Colors::Transparent;
	
	for(StarSystem& sys : State.Systems)
	{
		float alpha = sys.alphaAt(r->Context.cameraCenter());
		BackgroundStarColor  = AlphaBlend(BackgroundStarColor , sys.BackgroundStarColor, alpha);
		BackgroundFogColorsA = AlphaBlend(BackgroundFogColorsA, sys.BackgroundFogColorsA, alpha);
		BackgroundFogColorsB = AlphaBlend(BackgroundFogColorsB, sys.BackgroundFogColorsB, alpha);
		ForegroundStarColor  = AlphaBlend(ForegroundStarColor , sys.ForegroundStarColor, alpha);
	}
	
	r->clear(Colors::Black);
	r->drawRepeatedInf(gAssets.BackgroundStars, 0, 2.0f, 0.25f, BackgroundStarColor);
	r->drawRepeatedInf(gAssets.BackgroundFog, 0, 3.0f, 0.40f, BackgroundFogColorsA);
	r->drawRepeatedInf(gAssets.BackgroundFog, 0, 2.0f, 0.75f, BackgroundFogColorsB);
	r->drawRepeatedInf(gAssets.BackgroundStars, 0, 3.0f, 0.77f, ForegroundStarColor);
	if(State.Player)
		r->Context.Camera.Position = State.Player->Position;
	for(GameObject* obj : State.Objects)
	{
		obj->drawDebug (*r);
		obj->drawSprite(*r);
	}
	for(StarSystem& sys : State.Systems)
		sys.draw(r);
	
	r->flush();
	r->Context.setRenderTarget(window);
	r->clear(Colors::Black);
	r->Context.setShader(gAssets.ToneMappingShader);
	r->drawRenderpass(*HDRTarget);
}

void GameWorld::update(float deltaTime, InputMonitor* Input)
{
	if(State.Player)
		if(Controls.Rotation.direction())
			State.Player->DesiredDirection = Angle(Controls.Rotation.direction());
	
	State.update(deltaTime);
}

void GameState::update(float deltaTime)
{
	
	for(GameObject* obj : Objects)
	{
		obj->update(this, deltaTime);
		applyPhysics(obj, deltaTime);
	}
}

void GameState::applyPhysics(GameObject* obj, float dt)
{
	obj->Speed += obj->Acceleration * dt;
	obj->applyVecForce(-(obj->Speed * (Params.AirDrag * obj->Drag) * obj->Speed.length()), dt);
	
	obj->Rotation += Angle(obj->RotationSpeed * dt);
	
	Angle diff = Angle(obj->Speed) - obj->Rotation;
	obj->applyRotForce(diff * obj->Flow * (obj->Speed.length() / 1000), dt);
	obj->RotationSpeed -= (Params.AirFlow * obj->Flow * dt) * obj->RotationSpeed;

	obj->Position += obj->Speed * dt;
	obj->updateBounds();
}

void GameWorld::loadDefinitions(const std::string& folder)
{
  
}
