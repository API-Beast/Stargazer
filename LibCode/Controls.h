//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include <Springbok/Types.hpp>
#include <Springbok/Containers.hpp>

class InputDevice;
class InputMonitor;

struct DirectionControl
{
	Vec2F direction();
	
	static DirectionControl FourButton(InputMonitor* monitor, const std::string& k0, const std::string& k1, const std::string& k2, const std::string& k3);
	static DirectionControl FourButton(InputDevice * device, int k0, int k1, int k2, int k3);
	static DirectionControl Gamepad(InputMonitor* monitor, int xAxis, int yAxis);
	static DirectionControl Gamepad(InputDevice*  device, int xAxis, int yAxis);
	
	enum EType
	{
		Invalid,
		ButtonByName,
		ButtonByIndex,
		DPad,
		Mouse
	};
	
	struct ButtonDec
	{
		Vec2F Direction;
		int   Button;
	};
	
	struct ButtonNameDec
	{
		Vec2F Direction;
		std::string Name;
	};
	
	EType Type = Invalid;
	
	InputMonitor*   Monitor = nullptr; // One of these need to be specified
	InputDevice*    Device  = nullptr; // If a device is given this control will only respond to that specific device
	
	List<ButtonDec>     ButtonIndices;
	List<ButtonNameDec> ButtonNames;
	int XAxis;
	int YAxis;
	int MouseButton = -1;
	
	List<DirectionControl> Alternatives;
};

struct ActionControl
{
	bool isAvailable();
	bool consume();
	void reset();
	
	float ActionTimeOut = 0.05f; // The amount of time in seconds the action is remembered for if the button is not kept pressed down
	
	int   SuccesiveActions = 0;  // The time out is also used to remember succesive actions to detect things like double jump.
	float ActionTimer = 0.0f;
};

