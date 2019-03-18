#include "CooldownTracker.service.h"

#include <SDK/SpellInclude.h>
#include <SDK/Game.h>

#include <Common/ObjectHelper.h>

void CooldownTrackerService::DrawSpellSlot(int index, Vector3 basePosition)
{
	static const char* spellSlotArray[] =
	{
		ESpellSlot::ToString(ESpellSlot::Q),
		ESpellSlot::ToString(ESpellSlot::W),
		ESpellSlot::ToString(ESpellSlot::E),
		ESpellSlot::ToString(ESpellSlot::R),
		"D",
		"F"
	};
	
	float xPos = basePosition.x + (index * PADDING) - (CIRCLE_RADIUS / 2);
	Draw.Text(spellSlotArray[index], xPos, basePosition.y - CIRCLE_RADIUS * 0.8, text_alignment::lefted, 0, true, WHITE(), BLACK());
}

void CooldownTrackerService::DrawSpellReady(SpellDataInst* spell, int index, Vector3 basePosition)
{
	Draw.CircleFilled(basePosition.x + index * PADDING, basePosition.y, CIRCLE_RADIUS, 0, circle_type::full, CIRCLE_RESOLUTION, GREEN());
	DrawSpellSlot(index, basePosition);
}

void CooldownTrackerService::DrawSpellInCooldown(SpellDataInst* spell, int index, Vector3 basePosition)
{
	float cooldownRemaining = *spell->GetCooldownExpires() - Game::GetGameTime();
	float readyRatio = cooldownRemaining / *spell->GetCooldown();
	Draw.CircleFilled(basePosition.x + index * PADDING, basePosition.y, CIRCLE_RADIUS, 0, readyRatio, CIRCLE_RESOLUTION, RED());
	DrawSpellSlot(index, basePosition);
}

void CooldownTrackerService::DrawSpellNoMana(SpellDataInst* spell, int index, Vector3 basePosition)
{
	float cooldownRemaining = *spell->GetCooldownExpires() - Game::GetGameTime();
	float readyRatio = cooldownRemaining / *spell->GetCooldown();
	Draw.CircleFilled(basePosition.x + index * PADDING, basePosition.y, CIRCLE_RADIUS, 0, readyRatio, CIRCLE_RESOLUTION, BLUE_A(150));
	DrawSpellSlot(index, basePosition);
}

void CooldownTrackerService::DrawSpellUnavailable(SpellDataInst* spell, int index, Vector3 basePosition)
{
	Draw.CircleFilled(basePosition.x + index * PADDING, basePosition.y, CIRCLE_RADIUS, 0, full, CIRCLE_RESOLUTION, WHITE_A(150));
	DrawSpellSlot(index, basePosition);
}

void CooldownTrackerService::DrawFromSpellState(SpellDataInst* spell, ESpellState spellState, int index, Vector3 basePosition)
{
	switch (spellState)
	{
	case ESpellState::Ready:
		this->DrawSpellReady(spell, index, basePosition); return;
	case ESpellState::Cooldown:
		this->DrawSpellInCooldown(spell, index, basePosition); return;
	case ESpellState::NoMana:
		this->DrawSpellNoMana(spell, index, basePosition); return;

	default:
		this->DrawSpellUnavailable(spell, index, basePosition); return;
	}
}

void CooldownTrackerService::DrawHeroCooldowns(AIHeroClient* hero, Spellbook* spellBook)
{
	Vector3 basePosition;
	if (!hero->GetHpBarPosition(&basePosition))
		return;

	for (int i = 0; i <= ESpellSlot::Summoner2; ++i)
	{
		auto spell = spellBook->GetSpell((ESpellSlot::ESpellSlot)i);
		auto spellState = spellBook->GetSpellState((ESpellSlot::ESpellSlot)i);

		this->DrawFromSpellState(spell, spellState, i, basePosition);
	}
}

void CooldownTrackerService::OnEndScene()
{
	if (!Option::Get().enable_cooldown_tracker)
		return;

	auto heros = Common::ObjectList::mAllHeros;
	auto localPlayer = ObjectManager::GetPlayer();
	for (auto hero : heros) {

		if (hero == localPlayer) continue;
		if (!hero->IsAlive())continue;

		auto spellBook = hero->GetSpellbook();
		if (!spellBook)continue;

		this->DrawHeroCooldowns(hero, spellBook);
	}
}
