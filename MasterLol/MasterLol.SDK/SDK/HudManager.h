#pragma once
#include "stdafx.h"
#include "math/Vector.hpp"
#include "GameObject.h"

class GameCursor
{
public:
	char pad_0000[16]; //0x0000
	Vector3 UnderMouseObjPosition; //0x0010
	Vector3 Position; //0x001C
}; //Size: 0x0054

class HudManager
{
public:
	static GameCursor * GetGameCursor();
	static GameObject* GetUnderMouseObject();

	static bool IsWall(Vector3 worldPosition);
};
