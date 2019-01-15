#pragma once
#include "stdafx.h"
#include "SpellInfo.h"
#include "MissileClient.h"

class SpellCastInfo
{
public:
	MAKE_GET(CasterIndex, int16_t, Offsets::SpellCastInfo::CasterIndex);
	MAKE_GET(SourcePosition, Vector3, Offsets::SpellCastInfo::SourcePosition);
	MAKE_GET(DestinationPosition, Vector3, Offsets::SpellCastInfo::DestinationPosition);
	MAKE_GET(IsAutoAttack, bool, Offsets::SpellCastInfo::IsAutoAttack);
	MAKE_GET(TargetIndex, int16_t, Offsets::SpellCastInfo::TargetIndex);
	MAKE_GET(MissileClient, MissileClient*, Offsets::SpellCastInfo::MissileClient);
	MAKE_GET(WindupTime, float, Offsets::SpellCastInfo::WindupTime);
	MAKE_GET(AttackDelay, float, Offsets::SpellCastInfo::AttackDelay);
	MAKE_GET(Slot, ESpellSlot::ESpellSlot, Offsets::SpellCastInfo::Slot);

	SpellInfo* GetSpellInfo() { return *reinterpret_cast<SpellInfo**>(this + static_cast<__int32>(Offsets::SpellCastInfo::SpellInfo)); }

	//MissileClient* GetMissileClient()
	//{
	//	return *reinterpret_cast<MissileClient**>(this + static_cast<__int32>(Offsets::SpellCastInfo::MissileClient));
	//}

	inline std::string* GetMissileName()
	{
		auto sdata = *reinterpret_cast<DWORD**>(this);
		return reinterpret_cast<std::string*>(sdata + 0x6);
	}
};