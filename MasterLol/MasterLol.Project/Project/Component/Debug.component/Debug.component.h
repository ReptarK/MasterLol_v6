#pragma once
#include "../IComponent.h"
#include "DebugCollision.service.h"
#include "DebugMissile.service.h"
#include "DebugObject.service.h"

class DebugComponent : public IComponent
{
public:
	DebugComponent() : IComponent("DEBUG") {
		this->AddGameService<DebugCollisionService>();
		this->AddGameService<DebugMissileService>();
		this->AddGameService<DebugObjectService>();
	}

	virtual void RenderMenu() {
		Start(2);

		ImGui::Checkbox("Debug Collision", &Option::Get().enable_debug_collision);
		ImGui::Checkbox("Debug Missile", &Option::Get().enable_draw_debug_missile);
		ImGui::Checkbox("Log Missile", &Option::Get().enable_log_debug_hero_missile);

		ImGui::NextColumn();

		ImGui::Checkbox("Show LastHit Targets", &Option::Get().show_lasthit_targets);

		End();
	}
};

