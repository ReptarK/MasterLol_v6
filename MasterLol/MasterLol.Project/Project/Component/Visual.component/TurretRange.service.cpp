#include "TurretRange.service.h"

#include <Common/ObjectHelper.h>

void TurretRangeService::OnEndScene()
{
	if (!Option::Get().show_turrets_AA_range)
		return;

	auto player = ObjectManager::GetPlayer();
	auto playerPos = player->GetPos();

	auto allTurrets = Common::ObjectList::mAllTurrets;
	for (auto turret : allTurrets)
	{
		if (*turret->GetTeam() == *player->GetTeam())
			continue;

		auto addRadius = turret->GetBoundingRadius();
		Vector3 turretPos = turret->GetPos();
		float attackRangeSqr = turret->GetAttackRange() * turret->GetAttackRange();

		if (turretPos.DistToSqr(playerPos) < attackRangeSqr * 2)
			Draw.RangeCircle(turret->GetPos(), turret->GetAttackRange(), RED(), 0.2f);
	}
}
