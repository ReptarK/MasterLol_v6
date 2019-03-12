#pragma once
#include "../IComponent.h"

#include "FleeLogic.service.h"

class OrbwalkerComponent : public IComponent {

public:
	OrbwalkerComponent() : IComponent("ORBWALKER") {
		this->AddGameService<FleeLogicService>();
	}

	virtual void RenderMenu() {
		Start(2);
		ImGui::Text("Flee Key : [ X ]");
		ImGui::Text("Harass Key : [ C ]");
		ImGui::NextColumn();
		End();
	}
};
