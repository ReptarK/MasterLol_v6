#include "stdafx.h"
#include "Spellbook.h"
#include "SpellDataInst.h"
#include "Obj_AI_Base.h"
#include "ObjectManager.h"

SpellCastInfo * Spellbook::GetActiveSpell(){
	return *reinterpret_cast<SpellCastInfo**>(this + static_cast<int>(Offsets::Spellbook::ActiveSpell));
}

bool Spellbook::IsAutoAttacking()
{
	auto activeSpell = this->GetActiveSpell();
	return activeSpell && activeSpell->mIsAutoAttack;
}

ESpellState Spellbook::GetSpellState( ESpellSlot::ESpellSlot slot )
{
	return
		reinterpret_cast< ESpellState( __thiscall* )( void*, const ESpellSlot::ESpellSlot, const DWORD & ) >
		( Patchables::LolBase + fnGetSpellState )
		( this, slot, NULL );
}

SpellDataInst** Spellbook::GetSpells()
{
	return reinterpret_cast< SpellDataInst** >( this + static_cast< int >( Offsets::Spellbook::GetSpells ) );
}

SpellDataInst* Spellbook::GetSpell( ESpellSlot::ESpellSlot slot )
{
	return this->GetSpells()[( int )( slot )];
}

bool Spellbook::CastSpell( ESpellSlot::ESpellSlot slot, Vector3 dstPosition, Vector3 srcPosition, uint targetNetworkId )
{
	typedef int*( __thiscall *_fnCastSpell )( DWORD spellbook_addr, SpellDataInst* spellslot, ESpellSlot::ESpellSlot SlotID,
		Vector3* targetpos, Vector3* startpos, uint NetworkID );

	static _fnCastSpell oCastSpell = ( _fnCastSpell )( Patchables::LolBase + fnCastSpell );

	return oCastSpell( ( DWORD )this, this->GetSpell( slot ), slot, &dstPosition, &srcPosition, targetNetworkId );
}

void Spellbook::UpdateChargeableSpell( ESpellSlot::ESpellSlot slot, Vector3 position, bool releaseCast )
{
	typedef void( __thiscall* _fnUpdateChargeableSpell )(
		Spellbook* pSpellBook, SpellDataInst* pSpellDataInst, int slot, Vector3* pPosition, bool ReleaseCast
		);

	static _fnUpdateChargeableSpell oUpdateChargeableSpell = ( _fnUpdateChargeableSpell )( Patchables::LolBase + fnUpdateChargeableSpell );

	return oUpdateChargeableSpell( this, this->GetSpell( slot ), slot, &position, releaseCast );
}


