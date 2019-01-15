#pragma once
#include "stdafx.h"
#include "SpellInfo.h"
#include "StaticEnums.h"

class SpellDataInst
{
public:
	MAKE_GET(Level, int, Offsets::SpellDataInst::Level);
	MAKE_GET(CooldownExpires, float, Offsets::SpellDataInst::CooldownExpires);
	MAKE_GET(Ammo, int, Offsets::SpellDataInst::Ammo);
	MAKE_GET(AmmoRechargeStart, float, Offsets::SpellDataInst::AmmoRechargeStart);
	MAKE_GET(ToggleState, ToggleState, Offsets::SpellDataInst::ToggleState);
	MAKE_GET(Cooldown, float, Offsets::SpellDataInst::Cooldown);

	//MAKE_GET(SpellInfo, SpellInfo*, Offsets::SpellDataInst::SpellInfo);

	SpellInfo* GetSpellInfo();
};