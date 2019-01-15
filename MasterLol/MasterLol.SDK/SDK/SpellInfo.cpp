#include "stdafx.h"
#include "SpellInfo.h"

SpellData * SpellInfo::GetSpellData()
{
	return *reinterpret_cast<SpellData**>((DWORD)this + static_cast<__int32>(Offsets::SpellInfo::GetSpellData));
}
