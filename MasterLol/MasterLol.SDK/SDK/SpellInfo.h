#pragma once
#include "stdafx.h"
#include "SpellData.h"

class SpellInfo
{
public:
	SpellData * GetSpellData()
	{
		return *reinterpret_cast< SpellData** >( ( DWORD )this + static_cast< __int32 >( Offsets::SpellInfo::GetSpellData ) );
	}
};
