#pragma once
#include "../IComponent.h"

#include "TurretRange.service.h"
#include "PlayerVisual.service.h"

class VisualComponent : public IComponent
{

public:
	VisualComponent() : IComponent("VISUALS") {
		this->AddGameService<TurretRangeService>();
		this->AddGameService<PlayerVisualService>();
	}

	virtual void RenderMenu() {
		Start(2);

		ImGui::Text("PLAYER :");
		ImGui::Checkbox("AA Range", &g_Options.show_AA_range);
		ImGui::Checkbox("Q Range", &g_Options.show_Q_range);
		ImGui::Checkbox("W Range", &g_Options.show_W_range);
		ImGui::Checkbox("E Range", &g_Options.show_E_range);
		ImGui::Checkbox("R Range", &g_Options.show_R_range);

		ImGui::NextColumn();

		End();
	}
};
