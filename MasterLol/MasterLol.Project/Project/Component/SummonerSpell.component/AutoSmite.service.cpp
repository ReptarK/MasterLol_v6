#include "AutoSmite.service.h"

#include <Common/ObjectHelper.h>
#include <Common/SummonerSpells.h>

bool shouldCastSmite(Obj_AI_Base* target)
{
	__try {
		if (!target) return false;
		if (!Common::ObjectHelper::IsAttackable(target)) return false;
		if (!Common::ObjectHelper::IsInRange(target, Common::ActiveSummonerSpell::Get().Smite.CastRange)) return false;
		if (Common::ActiveSummonerSpell::Get().Smite.GetDamage() < *target->GetHealth()) return false;

		return true;
	}
	__except (1) { return false; }
}

void AutoSmiteService::OnUpdate()
{
	if (!Option::Get().enable_auto_smite)
		return;

	if (Common::ActiveSummonerSpell::Get().Smite.Slot == ESpellSlot::Unknown)
		return;

	auto allMinions = Common::ObjectList::mAllMinions;
	for (auto minion : allMinions)
	{
		if (!shouldCastSmite(minion))continue;

		if (Names::NameBeginWith(minion, Names::JungleMob::ToString(Names::JungleMob::SRU_Blue))) {
			Common::ActiveSummonerSpell::Get().Smite.Cast(minion);
			return;
		}

		if (Names::NameBeginWith(minion, Names::JungleMob::ToString(Names::JungleMob::SRU_Red))) {
			Common::ActiveSummonerSpell::Get().Smite.Cast(minion);
			return;
		}
	}

	if (shouldCastSmite(Common::ObjectList::mBaron)) {
		Common::ActiveSummonerSpell::Get().Smite.Cast(Common::ObjectList::mBaron);
		return;
	}

	if (shouldCastSmite(Common::ObjectList::mDragon)) {
		Common::ActiveSummonerSpell::Get().Smite.Cast(Common::ObjectList::mDragon);
		return;
	}
}

void AutoSmiteService::OnEndScene()
{
	if (!Option::Get().enable_auto_smite)
		return;

	if (Common::ActiveSummonerSpell::Get().Smite.Slot == ESpellSlot::Unknown)
		return;

	Draw.RangeCircle(
		ObjectManager::GetPlayer()->GetPos(),
		Common::ActiveSummonerSpell::Get().Smite.CastRange,
		Option::Get().smite_range_color,
		0.2f);
}
