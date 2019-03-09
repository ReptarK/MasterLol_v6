#include "VisualComponent.h"

#include <SDK/Options.h>
#include <SDK/ObjectManager.h>
#include <SDK/Obj_AI_Turret.h>
#include <SDK/Draw.h>

#include <Common/ObjectHelper.h>

void RenderPlayer(AIHeroClient * player)
{
	if (!player->IsAlive())
		return;

	auto addRadius = player->GetBoundingRadius();

	if (g_Options.show_AA_range)
		Draw.RangeCircle(player->GetPos(), player->GetUnitStats()->mAttackRange + addRadius, YELLOW(), 0.2);
}

void RenderTurrets(AIHeroClient * player)
{
	auto playerPos = player->GetPos();

	auto allTurrets = Common::ObjectList::mAllTurrets;
	for(auto turret : allTurrets)
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

void VisualComponent::OnEndScene(LPDIRECT3DDEVICE9 device)
{
	auto player = ObjectManager::GetPlayer();
	if (!player) return;

	RenderPlayer(player);
	RenderTurrets(player);
}

void VisualComponent::Initialize()
{
	EventHandler<EventIndex::OnDrawingEndScene, EventDefines::OnDrawingEndScene, IDirect3DDevice9*>::GetInstance()->Add(VisualComponent::OnEndScene);
}
