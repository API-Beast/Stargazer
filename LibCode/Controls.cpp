//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "Controls.h"
#include <Springbok/Platform/InputMonitor.h>
#include <Springbok/Platform/InputDevice.h>

DirectionControl DirectionControl::FourButton(InputMonitor* monitor, const std::string& k0, const std::string& k1, const std::string& k2, const std::string& k3)
{
	DirectionControl result;
	result.Monitor = monitor;
	result.Type    = ButtonByName;
	result.ButtonNames.pushBack({Vec2F( 0, -1), k0}); // W
	result.ButtonNames.pushBack({Vec2F( 0, +1), k1}); // S
	result.ButtonNames.pushBack({Vec2F(-1,  0), k2}); // A
	result.ButtonNames.pushBack({Vec2F(+1,  0), k3}); // D
	return result;
}

DirectionControl DirectionControl::FourButton(InputDevice* device, int k0, int k1, int k2, int k3)
{
	DirectionControl result;
	result.Device = device;
	result.Type   = ButtonByIndex;
	result.ButtonIndices.pushBack({Vec2F( 0, -1), k0}); // W
	result.ButtonIndices.pushBack({Vec2F( 0, +1), k1}); // S
	result.ButtonIndices.pushBack({Vec2F(-1,  0), k2}); // A
	result.ButtonIndices.pushBack({Vec2F(+1,  0), k3}); // D
	return result;
}

Vec2F DirectionControl::direction()
{
	Vec2F result;
	
	//
	// By Button Name
	//
	if(Type == ButtonByName)
	{
		int simultanousKeys = 0;
		//
		// Any Device
		//
		if(Monitor)
		{
			for(auto dec : ButtonNames)
				if(Monitor->isKeyPressed(dec.Name))
				{
					result += dec.Direction;
					simultanousKeys++;
				}
		}
		//
		// Specific Device
		//
		else if(Device)
		{
			for(auto dec : ButtonNames)
				if(Device->isKeyPressed(dec.Name))
				{
					result += dec.Direction;
					simultanousKeys++;
				}
		}
		
		
		if(simultanousKeys)
			result /= simultanousKeys;
	}
	//
	// By Button Index
	//
	else if(Type == ButtonByIndex)
	{
		int simultanousKeys = 0;
		//
		// Any Device
		//
		if(Monitor)
		{
			for(InputDevice* dev : Monitor->getDevices())
				for(auto dec : ButtonIndices)
					if(dev->isKeyPressed(dec.Button))
					{
						result += dec.Direction;
						simultanousKeys++;
					}
		}
		//
		// Specific Device
		//
		else if(Device)
		{
			for(auto dec : ButtonIndices)
				if(Device->isKeyPressed(dec.Button))
				{
					result += dec.Direction;
					simultanousKeys++;
				}
		}
		
		
		if(simultanousKeys)
			result /= simultanousKeys;
	}
	//
	// By Axis
	//
	else if(Type == DPad)
	{
		// Specific Device
		if(Device)
			result = Vec2F(Device->axisState(XAxis), Device->axisState(YAxis));
		// Any Device
		else if(Monitor)
			for(InputDevice* dev : Monitor->getDevices())
			{
				if(dev->numberOfAxes() > Max(XAxis, YAxis))
					result += Vec2F(dev->axisState(XAxis), dev->axisState(YAxis));
			}
	}
	
	// ...aaand finish
	if(result.length() > 1.00f)
		return result.normalized();
	return result;
}