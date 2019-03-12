#pragma once
#include "../IComponent.h"

class OrbwalkerComponent : public IComponent {

public:
	OrbwalkerComponent() : IComponent("ORBWALKER") {

	}

	virtual void RenderMenu() {
		Start(2);
		ImGui::NextColumn();
		End();
	}
};
