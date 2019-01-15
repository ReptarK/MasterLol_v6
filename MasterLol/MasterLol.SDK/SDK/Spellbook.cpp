#include "stdafx.h"
#include "Spellbook.h"
#include "SpellDataInst.h"
#include "Obj_AI_Base.h"
#include "ObjectManager.h"

MAKE_HOOK<convention_type::thiscall_r, int*, DWORD, SpellDataInst*, ESpellSlot::ESpellSlot, Vector3*, Vector3*, uint> CastSpell_Hook;

void __fastcall OnCastSpell(DWORD spellbook_addr, void* EDX, SpellDataInst* spellDataInst, ESpellSlot::ESpellSlot SlotID,
	Vector3* targetpos, Vector3* startpos, uint targetNetworkId)
{
	CastSpell_Hook.CallOriginal(spellbook_addr, spellDataInst, SlotID, targetpos, startpos, targetNetworkId);
}

void Spellbook::ApplyHooks()
{
	//CastSpell_Hook.Apply(Patchables::pCastSpell, OnCastSpell);
}

void Spellbook::ShutDown()
{
	//CastSpell_Hook.Remove();
}

SpellState Spellbook::GetSpellState(ESpellSlot::ESpellSlot slot)
{
	return
		reinterpret_cast<SpellState(__thiscall*)(void*, const ESpellSlot::ESpellSlot, const DWORD &)>
		(Patchables::LolBase + fnGetSpellState)
		(this, slot, NULL);
}

SpellDataInst** Spellbook::GetSpells()
{
	return reinterpret_cast<SpellDataInst**>(this + static_cast<int>(Offsets::Spellbook::GetSpells));
}

SpellDataInst* Spellbook::GetSpell(ESpellSlot::ESpellSlot slot)
{
	return this->GetSpells()[(int)(slot)];
}

bool Spellbook::CastSpell(ESpellSlot::ESpellSlot slot, Vector3 dstPosition, Vector3 srcPosition, uint targetNetworkId)
{
	typedef int*(__thiscall *_fnCastSpell)(DWORD spellbook_addr, SpellDataInst* spellslot, ESpellSlot::ESpellSlot SlotID,
		Vector3* targetpos, Vector3* startpos, uint NetworkID);

	static _fnCastSpell oCastSpell = (_fnCastSpell)(Patchables::LolBase + fnCastSpell);

	return oCastSpell((DWORD)this, this->GetSpell(slot), slot, &dstPosition, &srcPosition, targetNetworkId);
}


