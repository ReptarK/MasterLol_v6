#pragma once
#include "../IGameService.h"

#include <Common/ObjectHelper.h>
#include <SDK/SpellInclude.h>

class CooldownTrackerService : public IGameService {
	const int CIRCLE_RADIUS = 9;
	const int CIRCLE_RESOLUTION = 20;

	const int PADDING = (CIRCLE_RADIUS * 2) + 4;

	void DrawSpellSlot(int index, Vector3 basePosition);

	void DrawSpellReady(SpellDataInst* spell, int index, Vector3 basePosition);
	void DrawSpellInCooldown(SpellDataInst* spell, int index, Vector3 basePosition);
	void DrawSpellNoMana(SpellDataInst* spell, int index, Vector3 basePosition);
	void DrawSpellUnavailable(SpellDataInst* spell, int index, Vector3 basePosition);

	void DrawFromSpellState(SpellDataInst* spell, ESpellState spellState, int index, Vector3 basePosition);

	void DrawHeroCooldowns(AIHeroClient* hero, Spellbook* spellBook);

public:
	virtual void OnEndScene();
};

