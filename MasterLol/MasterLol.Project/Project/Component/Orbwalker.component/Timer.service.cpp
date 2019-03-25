#include "Timer.service.h"

#include <Common/GameFunctions.h>

#include <SDK/Game.h>
#include <SDK/AIHeroClient.h>
#include <SDK/HudManager.h>

bool TimerService::CanMove()
{
	return Game::GetGameTime() - this->mLastAttackTime > ObjectManager::GetPlayer()->GetAttackCastDelay() + Game::GetPing() / 1000.0f;
}

bool TimerService::CanAttack()
{
	return Game::GetGameTime() - this->mLastAttackTime > ObjectManager::GetPlayer()->GetAttackDelay() + (Game::GetPing() / 1000.0f);
}

void TimerService::OnUpdate()
{
}

void TimerService::OnProcessSpell(SpellCastInfo * spellCastInfo, Obj_AI_Base * caster)
{
	if (!caster || !caster->IsHero()) return;
	AIHeroClient* heroCaster = (AIHeroClient*)caster;

	if (heroCaster != ObjectManager::GetPlayer()) return;
	if (!spellCastInfo->mIsAutoAttack) return;

	TimerService::Get().mLastAttackTime = Game::GetGameTime();
}

void TimerService::OnEndScene()
{
	auto player = ObjectManager::GetPlayer();
	if (!player) return;

	Draw.RangeCircle(player->GetPos(), player->GetBoundingRadius(), TimerService::Get().CanMove() && TimerService::Get().CanAttack() ? GREEN() : RED(), 1);
}

