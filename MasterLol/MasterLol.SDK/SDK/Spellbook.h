#pragma once
#include "stdafx.h"
#include "StaticEnums.h"
#include "math/Vector.hpp"
#include "Hooks.h"

class SpellDataInst;
class SpellData;

class Spellbook
{
public:
	static void ApplyHooks();
	static void ShutDown();


	SpellState GetSpellState(ESpellSlot::ESpellSlot);

	SpellDataInst** GetSpells();
	SpellDataInst* GetSpell(ESpellSlot::ESpellSlot slot);

	bool CastSpell(ESpellSlot::ESpellSlot slot, Vector3 dstPosition, Vector3 srcPosition = Vector3(0, 0, 0), uint targetNetworkId = 0);
};
