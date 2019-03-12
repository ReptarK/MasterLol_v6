#pragma once
#include "../IComponent.h"
#include "AutoSmite.service.h"

class SummonerSpellComponent : public IComponent
{
	const ImColor DEFAULT_SMITE_RANGE_COLOR = ImColor(90, 190, 60);

public:
	SummonerSpellComponent() : IComponent("SUMMONER SPELLS") {
		this->AddGameService<AutoSmiteService>();
	}

	virtual void RenderMenu() {
		Start(2);

		// Auto Smite
		ImGui::Checkbox("Auto Smite ('M')", &Option::Get().enable_auto_smite);
		ImGui::ColorPicker3("##smite color", (float*)&Option::Get().smite_range_color, 
			ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
		if (ImGui::Button("Default Color"))
			Option::Get().smite_range_color = DEFAULT_SMITE_RANGE_COLOR;

		ImGui::NextColumn();
		End();
	}
};
