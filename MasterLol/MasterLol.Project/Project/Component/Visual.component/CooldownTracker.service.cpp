#include "CooldownTracker.service.h"

#include <SDK/SpellInclude.h>
#include <SDK/Game.h>

#include <Common/ObjectHelper.h>

void CooldownTrackerService::DrawCooldown(AIHeroClient* hero, Spellbook* spellBook)
{
	static const int CIRCLE_RADIUS = 8;
	static const int CIRCLE_RESOLUTION = 20;

	Vector3 screenPosition;
	if (!Draw.WorldToScreen(hero->GetPos(), &screenPosition))
		return;

	float gameTime = Game::GetGameTime();

	auto spell = spellBook->GetSpell(ESpellSlot::Q);
	auto spellState = spellBook->GetSpellState(ESpellSlot::Q);

	if (spellState == ESpellState::Ready) 
	{
		Draw.CircleFilled(screenPosition.x, screenPosition.y, CIRCLE_RADIUS, 0, circle_type::full, CIRCLE_RESOLUTION, GREEN());
		Draw.Text("Q", screenPosition.x - CIRCLE_RADIUS / 2, screenPosition.y - CIRCLE_RADIUS / 2, text_alignment::centered, 0, false, WHITE());

		return;
	}
	else if(spellState == ESpellState::Cooldown)
	{
		// SPELL NOT READY
		float cooldownRemaining = *spell->GetCooldownExpires() - gameTime;
		if (cooldownRemaining < 0) {
			// Impossible ?
			Draw.CircleFilled(screenPosition.x, screenPosition.y, CIRCLE_RADIUS, 0, circle_type::full, CIRCLE_RESOLUTION, RED());
			Draw.Text("Q", screenPosition.x - CIRCLE_RADIUS / 2, screenPosition.y - CIRCLE_RADIUS / 2, text_alignment::centered, 0, false, WHITE());
			return;
		}

		float readyRatio = cooldownRemaining / *spell->GetCooldown();
		Draw.CircleFilled(screenPosition.x, screenPosition.y, CIRCLE_RADIUS, 0, readyRatio, CIRCLE_RESOLUTION, RED());
		Draw.Text("Q", screenPosition.x - CIRCLE_RADIUS / 2, screenPosition.y - CIRCLE_RADIUS / 2, text_alignment::centered, 0, false, WHITE());

		return;
	}
	else
	{
		Draw.Text("-", screenPosition.x, screenPosition.y, centered, 0, false, WHITE());
	}






	//static const char* spellSlotArray[] = {
	//	ESpellSlot::ToString(ESpellSlot::Q),
	//	ESpellSlot::ToString(ESpellSlot::W),
	//	ESpellSlot::ToString(ESpellSlot::E),
	//	ESpellSlot::ToString(ESpellSlot::R),
	//};

	//for (int i = 0; i <= ESpellSlot::R; ++i)
	//{

	//}
}

void CooldownTrackerService::OnEndScene()
{
	auto heros = Common::ObjectList::mAllHeros;
	for (auto hero : heros) {

		if (!hero->IsAlive())continue;

		auto spellBook = hero->GetSpellbook();
		if (!spellBook)continue;

		this->DrawCooldown(hero, spellBook);
	}
}
