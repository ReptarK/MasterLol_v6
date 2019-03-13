#pragma once
#include "../Option.h"

#include <SDK/Inputs.h>
#include <SDK/Draw.h>
#include <SDK/MissileClient.h>
#include <SDK/Obj_AI_Base.h>

class IGameService {

public:
	virtual void OnUpdate() {}
	virtual void OnEndScene() {}
	virtual void OnMissileProcessSpell(MissileClient*, Obj_AI_Base*) {}
};
