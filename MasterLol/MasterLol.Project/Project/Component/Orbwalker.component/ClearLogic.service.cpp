#include "ClearLogic.service.h"
#include "Timer.service.h"

#include <SDK/HudManager.h>
#include <SDK/Game.h>

#include <Common/GameFunctions.h>
#include <Common/ObjectHelper.h>

bool ClearLogicService::IsValidTarget(Obj_AI_Base * unit)
{
	AIHeroClient* player = ObjectManager::GetPlayer();
	if (!unit)
		return false;

	if (!unit->IsAlive())
		return false;

	if (!unit->IsTargetable())
		return false;

	// Check for teams
	if (*unit->GetTeam() == *player->GetTeam())
		return false;

	if (*unit->GetMaxHealth() <= 6)
		return false;

	// Check for range
	if (player->IsMelee()) {
		if (!Common::ObjectHelper::IsInRange(unit, player->GetUnitStats()->mAttackRange * 1.4f))
			return false;
	}
	else if (!Common::ObjectHelper::IsInRange(unit, player->GetUnitStats()->mAttackRange))
		return false;

	return true;
}

Obj_AI_Base * ClearLogicService::FindBestTarget()
{
	std::vector<Obj_AI_Base*> validMinion = std::vector<Obj_AI_Base*>();
	auto allMinion = Common::ObjectList::mAllMinions;
	for (auto minion : allMinion)
	{
		if (this->IsValidTarget(minion))
			validMinion.push_back(minion);
	}

	return Common::ObjectHelper::GetLowestHp(validMinion);

}

void ClearLogicService::OnUpdate()
{
	if (!InputSys::Get().IsKeyDown(this->ACTIVE_KEY))
		return;

	if (!TimerService::Get().CanAttack()) {
		if (TimerService::Get().CanMove())
			GameFunctions::IssueOrder(HudManager::GetGameCursor()->Position, EGameObjectOrder::MoveTo);

		return;
	}

	Obj_AI_Base* target = this->FindBestTarget();

	if (!target)
	{
		if (TimerService::Get().CanMove())
			GameFunctions::IssueOrder(HudManager::GetGameCursor()->Position, EGameObjectOrder::MoveTo);

		return;
	}

	if (TimerService::Get().CanAttack()) {
		TimerService::Get().mSentAttackTime = Game::GetGameTime();
		GameFunctions::IssueOrder(target->GetPos(), EGameObjectOrder::AttackUnit, target);
	}
}
