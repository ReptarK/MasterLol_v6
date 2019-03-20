#pragma once
#include "../IGameService.h"

class DebugProcessSpellService : public IGameService {

	void DrawSpell(SpellCastInfo*);
	void LogSpell(SpellCastInfo*, Obj_AI_Base* caster);

public:
	DebugProcessSpellService() {
	}

	virtual void OnEndScene();
	virtual void OnProcessSpell(SpellCastInfo*, Obj_AI_Base* caster);
};
