#pragma once
#include "stdafx.h"

class SpellData
{
public:
	MAKE_GET(SpellName, char*, Offsets::SpellData::SpellName);
	MAKE_GET(MissileName, char*, Offsets::SpellData::MissileName);
	MAKE_SPELL_DATA_ARRAY(EffectAmount, float, Offsets::SpellData::EffectAmount);
	MAKE_GET(Cooeficient, float, Offsets::SpellData::Coefficient);
	MAKE_GET(Coefficient2, float, Offsets::SpellData::Coefficient2);
	MAKE_SPELL_DATA_ARRAY(CooldownTime, float, Offsets::SpellData::CooldownTime);
	MAKE_SPELL_DATA_ARRAY(CastRange, float, Offsets::SpellData::CastRange);
	MAKE_GET(CastRadius, float, Offsets::SpellData::CastRadius);
	MAKE_GET(CastConeAngle, float, Offsets::SpellData::CastConeAngle);
	MAKE_GET(CastConeDistance, float, Offsets::SpellData::CastConeDistance);
	MAKE_GET(CastTargetAdditionalUnitsRadius, float, Offsets::SpellData::CastTargetAdditionalUnitsRadius);
	MAKE_GET(LuaOnMissileUpdateDistanceInterval, float, Offsets::SpellData::LuaOnMissileUpdateDistanceInterval);
	MAKE_GET(CastType, float, Offsets::SpellData::CastType);
	MAKE_GET(SpellDamageRatio, float, Offsets::SpellData::SpellDamageRatio);
	MAKE_GET(PhysicalDamageRatio, float, Offsets::SpellData::PhysicalDamageRatio);
	MAKE_GET(MissileSpeed, float, Offsets::SpellData::MissileSpeed);
	MAKE_SPELL_DATA_ARRAY(ManaCost, float, Offsets::SpellData::ManaCost);
	MAKE_GET(TargetingType, float, Offsets::SpellData::TargetingType);
};
