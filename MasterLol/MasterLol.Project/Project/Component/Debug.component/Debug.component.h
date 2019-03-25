#pragma once
#include "../IComponent.h"
#include "DebugCollision.service.h"
#include "DebugMissile.service.h"
#include "DebugObject.service.h"
#include "DebugProcessSpell.service.h"
#include "DebugNavigation.service.h"
#include "DebugPrediction.service.h"

class DebugComponent : public IComponent
{
public:
	DebugComponent() : IComponent("DEBUG") {
		this->AddGameService<DebugCollisionService>();
		this->AddGameService<DebugMissileService>();
		this->AddGameService<DebugObjectService>();
		this->AddGameService<DebugProcessSpellService>();
		this->AddGameService<DebugNavigationService>();
		this->AddGameService<DebugPredictionService>();
	}

	virtual void RenderMenu() {
		Start(2);

		ImGui::Checkbox("Debug Collision", &Option::Get().enable_debug_collision);
		ImGui::Checkbox("Debug Navigation", &Option::Get().enable_debug_navigation);
		ImGui::Checkbox("Debug Prediction", &Option::Get().enable_debug_prediction);
		ImGui::Checkbox("Log Missile", &Option::Get().log_missile);
		ImGui::Checkbox("Log Process Spell", &Option::Get().log_process_spell_hero);
		ImGui::Checkbox("Show Process Spell", &Option::Get().show_process_spell);

		ImGui::NextColumn();

		ImGui::Checkbox("Show LastHit Targets", &Option::Get().show_lasthit_targets);

		End();
	}
};

