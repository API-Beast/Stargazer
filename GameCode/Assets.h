//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Graphics.hpp>

struct Assets
{
	void init();
	
	BitmapFont Font;
	Image BackgroundFog;
	Image BackgroundStars;
	Image SystemDebugSprite;
	Image SystemRadiusSprite;
	LineStyle Arrow;
	ShaderProgram ToneMappingShader;
};

extern Assets gAssets;
