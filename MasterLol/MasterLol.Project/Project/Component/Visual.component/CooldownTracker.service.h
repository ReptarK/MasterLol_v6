#pragma once
#include "../IGameService.h"

#include <Common/ObjectHelper.h>
#include <SDK/SpellInclude.h>

class CooldownTrackerService : public IGameService {

	void DrawCooldown(AIHeroClient* hero, Spellbook* spellBook);

public:
	virtual void OnEndScene();
};

