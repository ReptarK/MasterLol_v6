#pragma once
#include "stdafx.h"
#include "math/Vector.hpp"
#include "GameObject.h"

class GameCursor
{
public:
	static Vector3 GetPos();
	static GameObject* GetUnderMouseObject();
};
