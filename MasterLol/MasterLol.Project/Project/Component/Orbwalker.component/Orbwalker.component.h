#pragma once
#include "../IComponent.h"

#include "FleeLogic.service.h"
#include "ClearLogic.service.h"
#include "Timer.service.h"

class OrbwalkerComponent : public IComponent {
public:

	OrbwalkerComponent() : IComponent("ORBWALKER") {
		TimerService::Get().Initialize();
		this->AddGameService<FleeLogicService>();
		this->AddGameService<ClearLogicService>();
	}

	virtual void RenderMenu() {
		Start(2);
		ImGui::Text("Flee Key : [ X ]");
		ImGui::Text("Harass Key : [ C ]");
		ImGui::NextColumn();
		End();
	}
};
