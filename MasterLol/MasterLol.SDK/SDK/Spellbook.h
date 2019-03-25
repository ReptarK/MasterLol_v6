#pragma once
#include "stdafx.h"
#include "StaticEnums.h"
#include "math/Vector.hpp"
#include "Hooks.h"
#include "SpellCastInfo.h"

class SpellDataInst;
class SpellData;

class Spellbook
{
public:

	MAKE_GET( ManaCostQ, float, Offsets::Spellbook::ManaCostQ );
	MAKE_GET( ManaCostW, float, Offsets::Spellbook::ManaCostW );
	MAKE_GET( ManaCostE, float, Offsets::Spellbook::ManaCostE );
	MAKE_GET( ManaCostR, float, Offsets::Spellbook::ManaCostR );

	SpellCastInfo* GetActiveSpell();
	bool IsAutoAttacking();

	ESpellState GetSpellState( ESpellSlot::ESpellSlot );

	SpellDataInst** GetSpells();
	SpellDataInst* GetSpell( ESpellSlot::ESpellSlot slot );

	bool CastSpell( ESpellSlot::ESpellSlot slot, Vector3 dstPosition, Vector3 srcPosition = Vector3( 0, 0, 0 ), uint targetNetworkId = 0 );
	void UpdateChargeableSpell( ESpellSlot::ESpellSlot slot, Vector3 position, bool releaseCast );
};
