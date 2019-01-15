#include "stdafx.h"
#include "SpellDataInst.h"

SpellInfo * SpellDataInst::GetSpellInfo()
{
	return *reinterpret_cast<SpellInfo**>((DWORD)this + static_cast<__int32>(Offsets::SpellDataInst::SpellInfo));
}
