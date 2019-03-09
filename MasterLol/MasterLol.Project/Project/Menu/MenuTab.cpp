#include "MenuTab.h"

void MenuTab::Start(int nbColumns)
{
	bool placeholder_true = true;
	auto& style = ImGui::GetStyle();
	float group_w = ImGui::GetCurrentWindow()->Size.x - style.WindowPadding.x * 2;
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ style.WindowPadding.x, style.ItemSpacing.y });

	ImGui::Columns(nbColumns, nullptr, true);
	for (int i = 1; i <= nbColumns; ++i)
		ImGui::SetColumnOffset(i, group_w / (float)nbColumns);
}

void VisualsTab::Render()
{
	MenuTab::Start(2);

	ImGui::Text("PLAYER :");
	ImGui::Checkbox("AA Range", &g_Options.show_AA_range);
	ImGui::Checkbox("Q Range", &g_Options.show_Q_range);
	ImGui::Checkbox("W Range", &g_Options.show_W_range);
	ImGui::Checkbox("E Range", &g_Options.show_E_range);
	ImGui::Checkbox("R Range", &g_Options.show_R_range);

	ImGui::NextColumn();

	MenuTab::End();
}

void CommonTab::Render()
{
	MenuTab::Start(2);

	ImGui::Text("COMMON");


	ImGui::NextColumn();

	MenuTab::End();
}

void DebugTab::Render()
{
	MenuTab::Start(2);

	ImGui::Checkbox("Debug Collision", &g_Options.enable_debug_collision);
	ImGui::Checkbox("Show LastHit Targets", &g_Options.show_lasthit_targets);

	ImGui::NextColumn();

	MenuTab::End();
}
