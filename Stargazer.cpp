//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Stargazer.h"

Stargazer::Stargazer()
{
	Surface  = new GameSurface("Stargazer", GameSurface::Windowed);
	Input    = new InputMonitor(Surface);
	Renderer = new SpriteRenderer(Surface);
}

Stargazer::~Stargazer()
{
	delete Surface;
	delete Input;
	delete Renderer;
}

int Stargazer::execute()
{	
	Clock.start();
	while(!IsFinished)
	{
		// Input
		if(Surface->closeRequested())
			IsFinished = true;
		
		// Updating & Drawing
		float deltaTime = Clock.elapsed();
		Clock.start();
		Renderer->clear();
		World.update(deltaTime);
		World.draw(Renderer);
		Renderer->flush();
		Surface->switchBuffers();
	}
	return 0;
}
