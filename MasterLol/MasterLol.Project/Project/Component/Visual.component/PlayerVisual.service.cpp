#include "PlayerVisual.service.h"

#include <Common/ObjectHelper.h>

void PlayerVisualService::OnEndScene()
{
	auto player = ObjectManager::GetPlayer();

	if (!player->IsAlive())
		return;

	auto addRadius = player->GetBoundingRadius();

	if (Option::Get().show_AA_range)
		Draw.RangeCircle(player->GetPos(), player->GetUnitStats()->mAttackRange + addRadius, YELLOW_A(25), 0.1f);
}
