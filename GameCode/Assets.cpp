//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Assets.h"

Assets gAssets;

void Assets::init()
{
	Font.loadGrid(Image("Font16.png"), 0, 16);
	BackgroundFog = Image("Background/Fog01.png");
	BackgroundStars = Image("Background/Stars.png");
	SystemDebugSprite = Image("Systems/Debug.png");
	Arrow = LineStyle(Image("HUD/Arrow.png"), 10, 10);
	
	ToneMappingShader = ShaderProgram("ToneMap.Fragment.glsl");
	ToneMappingShader.FragmentShader->compile();
	ToneMappingShader.link();
}
