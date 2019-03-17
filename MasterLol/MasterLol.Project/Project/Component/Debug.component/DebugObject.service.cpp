#include "DebugObject.service.h"

#include <Common/ObjectHelper.h>
#include <Common/Damage.h>

void DebugObjectService::OnEndScene()
{
	if (Option::Get().show_lasthit_targets)
	{
		auto AARange = ObjectManager::GetPlayer()->GetUnitStats()->mAttackRange;
		auto AADamage = Common::Damage::GetStaticAutoAttackDamage();

		auto minions = Common::ObjectList::mAllMinions;
		for (auto minion : minions)
		{
			if (!minion->IsMinion()) continue;
			if (!Common::ObjectHelper::IsValidTarget(minion, AARange))continue;

			auto damageOnTarget = Common::Damage::GetAutoAttackDamage(minion, AADamage);
			if (*minion->GetHealth() < damageOnTarget) {
				Draw.CircleFilled(minion->GetPos(), minion->GetBoundingRadius() / 2, GREEN_A(150));
			}
		}
	}
}
