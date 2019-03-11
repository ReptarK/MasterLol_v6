#include "PlayerVisual.service.h"

#include <SDK/Draw.h>
#include <SDK/Options.h>

#include <Common/ObjectHelper.h>

void PlayerVisualService::OnEndScene()
{
	auto player = ObjectManager::GetPlayer();

	if (!player->IsAlive())
		return;

	auto addRadius = player->GetBoundingRadius();

	if (g_Options.show_AA_range)
		Draw.RangeCircle(player->GetPos(), player->GetUnitStats()->mAttackRange + addRadius, YELLOW(), 0.1f);
}
