#pragma once
#include "Obj_AI_Base.h"
#include <map>

class Obj_AI_Turret
	: public Obj_AI_Base
{
public:
	float GetAttackRange() { return 830.0f + this->GetBoundingRadius(); }
};
