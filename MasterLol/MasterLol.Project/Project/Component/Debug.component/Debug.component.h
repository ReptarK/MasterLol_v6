#pragma once
#include "../IComponent.h"
#include "DebugCollision.service.h"
#include "DebugMissile.service.h"
#include "DebugObject.service.h"
#include "DebugProcessSpell.service.h"

class DebugComponent : public IComponent
{
public:
	DebugComponent() : IComponent("DEBUG") {
		this->AddGameService<DebugCollisionService>();
		this->AddGameService<DebugMissileService>();
		this->AddGameService<DebugObjectService>();
		this->AddGameService<DebugProcessSpellService>();
	}

	virtual void RenderMenu() {
		Start(2);

		ImGui::Checkbox("Debug Collision", &Option::Get().enable_debug_collision);
		ImGui::Checkbox("Log Missile", &Option::Get().log_missile);
		ImGui::Checkbox("Log Process Spell", &Option::Get().log_process_spell_hero);
		ImGui::Checkbox("Show Process Spell", &Option::Get().show_process_spell);

		ImGui::NextColumn();

		ImGui::Checkbox("Show LastHit Targets", &Option::Get().show_lasthit_targets);

		End();
	}
};

