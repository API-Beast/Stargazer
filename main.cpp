//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include <iostream>
#include "Stargazer.h"
#include <Springbok/Foundation.hpp>

int main(int argc, char **argv)
{
	ResourceManager::GetInstance()->findPrimaryResourcePath({FileSystem::ParentPath(__FILE__)+"/Assets", "./Assets"});
	Stargazer game;
	return game.execute();
}
