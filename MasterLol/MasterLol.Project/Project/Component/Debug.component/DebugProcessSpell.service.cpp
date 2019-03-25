#include "DebugProcessSpell.service.h"

#include <SDK/Game.h>

#include <Common/ObjectHelper.h>
#include <Common/GameEvent.h>

void DebugProcessSpellService::DrawSpell(SpellCastInfo * spell)
{
	Draw.Line(spell->mStartPosition, spell->mEndPosition,
		20, WHITE_A(50));
}

void DebugProcessSpellService::OnEndScene()
{
	if (!Option::Get().show_process_spell)
		return;

	auto allActiveSpell = Common::OnProcessSpell::mActiveProcessSpell;
	for (auto it = allActiveSpell.begin(); it != allActiveSpell.end(); ++it)
	{
		SpellCastInfo* spell = it->second;
		if (!spell) continue;

		if (spell->mSlot < 0)
			continue;

		this->DrawSpell(spell);
	}
}

void DebugProcessSpellService::LogSpell(SpellCastInfo * spell, Obj_AI_Base * caster)
{
	printf("OnProcessSpell :\n\
			\t Spell : %s,\n \
			\t SpellInfo : %#x,\n \
			\t CastType : %d,\n \
			\t Slot : %d,\n \
			\t Is AA ? : %s,\n \
			\t Caster : %s\n\
			\t WindupTime : %f\n\
			\t CastTime : %f\n",
		spell->mSpellInfo->GetSpellData()->SpellName,
		spell->mSpellInfo,
		spell->mSpellInfo->GetSpellData()->CastType,
		spell->mSlot,
		spell->mIsAutoAttack ? "true" : "false",
		caster->GetName().c_str(),
		spell->mWindupTime,
		spell->mCastTime);
}

void DebugProcessSpellService::OnProcessSpell(SpellCastInfo* spell, Obj_AI_Base* caster)
{
	if (!Option::Get().log_process_spell_hero)
		return;

	if (!caster)
		return;

	__try { this->LogSpell(spell, caster); }
	__except (1) {}
}
