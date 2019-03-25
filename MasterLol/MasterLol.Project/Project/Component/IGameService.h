#pragma once
#include "../Option.h"

#include <SDK/Inputs.h>
#include <SDK/Draw.h>
#include <SDK/SpellCastInfo.h>
#include <SDK/Obj_AI_Base.h>

class IGameService {
public:
	virtual void OnUpdate() {}
	virtual void OnEndScene() {}
	virtual void OnProcessSpell(SpellCastInfo*, Obj_AI_Base* caster) {}
	virtual void OnCreateMissile(MissileClient*, Obj_AI_Base* caster) {}
};
