#pragma once
#include <SDK/Options.h>

#include <SDK/imGui/imgui_impl_dx9.h>
#include <SDK/ImGui/imgui.h>
#include <SDK/ImGui/imgui_internal.h>

namespace MenuTabs
{
	void start( int nbColumns )
	{
		bool placeholder_true = true;
		auto& style = ImGui::GetStyle();
		float group_w = ImGui::GetCurrentWindow()->Size.x - style.WindowPadding.x * 2;
		ImGui::PushStyleVar( ImGuiStyleVar_ItemSpacing, ImVec2 { style.WindowPadding.x, style.ItemSpacing.y } );

		ImGui::Columns( nbColumns, nullptr, true );
		for ( int i = 1; i <= nbColumns; ++i )
			ImGui::SetColumnOffset( i, group_w / ( float )nbColumns );
	}

	void end()
	{
		ImGui::PopStyleVar();
	}


	void RenderCommonTab()
	{
		start( 2 );

		ImGui::Text( "Test RenderTab" );
		ImGui::NextColumn();
		ImGui::Text( "Col 2" );

		end();

	}

	void RenderVisualsTab()
	{
		start( 2 );

		ImGui::Text( "PLAYER" );
		ImGui::Checkbox( "AA Range", &g_Options.show_AA_range );
		ImGui::Checkbox( "Q Range", &g_Options.show_Q_range );
		ImGui::Checkbox( "W Range", &g_Options.show_W_range );
		ImGui::Checkbox( "E Range", &g_Options.show_E_range );
		ImGui::Checkbox( "R Range", &g_Options.show_R_range );

		ImGui::NextColumn();
		ImGui::Text( "Col 2" );

		end();
	}

	void RenderMickTab()
	{
		start( 2 );

		ImGui::Text( "Test RenderMickTab" );
		ImGui::NextColumn();
		ImGui::Text( "Col 2" );

		end();
	}
}






