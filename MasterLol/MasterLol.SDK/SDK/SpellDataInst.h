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
	MAKE_GET(EToggleState, EToggleState, Offsets::SpellDataInst::ToggleState);
	MAKE_GET(Cooldown, float, Offsets::SpellDataInst::Cooldown);

	SpellInfo* GetSpellInfo()
	{
		return *reinterpret_cast< SpellInfo** >( ( DWORD )this + static_cast< __int32 >( Offsets::SpellDataInst::SpellInfo ) );
	}
};