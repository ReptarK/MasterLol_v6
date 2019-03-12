#include "Menu.h"

#include <SDK/imGui/imgui_impl_dx9.h>
#include <SDK/ImGui/imgui.h>
#include <SDK/ImGui/imgui_internal.h>

#include <SDK/D3DHooks.h>
#include <SDK/Inputs.h>
#include <SDK/D3DHooks.h>

bool Menu::_isVisible = false;
ImGuiStyle Menu::_style;

// ImGui
bool p_open = true;

static int active_sidebar_tab = 0;

static float get_sidebar_item_width() { return 150.0f; }
static float get_sidebar_item_height() { return  50.0f; }

ImVec2 Menu::GetSidebarSize()
{
	int menuSize = ComponentsManager::mComponents.size();
	if (menuSize < 1)
		menuSize = 1;

	float padding = 10.0f;
	float size_w = padding * 2.0f + get_sidebar_item_width();
	float size_h = padding * 2.0f + (menuSize * get_sidebar_item_height());

	return ImVec2{ size_w, ImMax(325.0f, size_h) };
}

void Menu::RenderTabs(int& activetab, float w, float h, bool sameline)
{
	ComponentsManager::mComponents.at(activetab)->mIsActive = true;

	for (auto i = 0u; i < ComponentsManager::mComponents.size(); ++i) {
		if (ImGui::ToggleButton(ComponentsManager::mComponents.at(i)->mTabName, &ComponentsManager::mComponents.at(i)->mIsActive, ImVec2 { w, h })) {
			activetab = i;
		}
		if (sameline && i < ComponentsManager::mComponents.size() - 1)
			ImGui::SameLine();
	}
}

void Menu::OnEndScene(LPDIRECT3DDEVICE9 device)
{
	if (!GetAsyncKeyState(VK_LSHIFT))
		return;

	ImGui_ImplDX9_NewFrame();

	ImGui::PushStyle(_style);
	ImGui::SetNextWindowPos(ImVec2{ 0, 0 }, ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2{ 800, 0 }, ImGuiSetCond_Once);

	const auto sidebar_size = Menu::GetSidebarSize();
	static int active_sidebar_tab = 0;

	ImGui::Begin("MasterLol", &Menu::_isVisible,
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize);

	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
	{
		ImGui::BeginGroupBox("##sidebar", sidebar_size);
		{
			ImGui::GetCurrentWindow()->Flags &= ~ImGuiWindowFlags_ShowBorders;

			Menu::RenderTabs(active_sidebar_tab, get_sidebar_item_width(), get_sidebar_item_height(), false);
		}
		ImGui::EndGroupBox();
	}
	ImGui::PopStyleVar();
	ImGui::SameLine();

	auto size = ImVec2{ 0.0f, sidebar_size.y };
	ImGui::BeginGroupBox("##body", size);
	ComponentsManager::mComponents.at(active_sidebar_tab)->RenderMenu();

	ImGui::EndGroupBox();
	ImGui::End();
	ImGui::Render();
}

void Menu::OnReset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params)
{
	Menu::OnDeviceLost();

	auto hr = D3D::D3DHooks::Get().originalReset(device, params);

	if (hr >= 0)
		Menu::OnDeviceReset();
}

void Menu::Initialize()
{
	_isVisible = true;

	ImGuiIO& io = ImGui::GetIO();
	io.DeltaTime = 1.f / 60.f;
	D3DDEVICE_CREATION_PARAMETERS d3dcp{ 0 };
	D3D::D3DHooks::Get().GetDevice()->GetCreationParameters(&d3dcp);
	ImGui_ImplDX9_Init(InputSys::Get().GetMainWindow(), D3D::D3DHooks::Get().GetDevice());
	CreateStyle();

	EventHandler<EventIndex::OnDrawingEndScene, EventDefines::OnDrawingEndScene, IDirect3DDevice9*>::GetInstance()->Add(Menu::OnEndScene);
	EventHandler<EventIndex::OnReset, EventDefines::OnReset, IDirect3DDevice9*, D3DPRESENT_PARAMETERS*>::GetInstance()->Add(Menu::OnReset);
}

void Menu::Shutdown()
{
	ImGui_ImplDX9_Shutdown();
}

void Menu::OnDeviceLost()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
}

void Menu::OnDeviceReset()
{
	ImGui_ImplDX9_CreateDeviceObjects();
}

void Menu::CreateStyle()
{

	_style.Alpha = 1.0f;                                // Global alpha applies to everything in ImGui
	_style.WindowPadding = ImVec2(10, 10);                      // Padding within a window
	_style.WindowMinSize = ImVec2(100, 100);                    // Minimum window size
	_style.WindowRounding = 0.0f;                                // Radius of window corners rounding. Set to 0.0f to have rectangular windows
	_style.WindowTitleAlign = ImVec2(0.0f, 0.5f);                  // Alignment for title bar text
	_style.ChildWindowRounding = 0.0f;                                // Radius of child window corners rounding. Set to 0.0f to have rectangular child windows
	_style.FramePadding = ImVec2(5, 5);                        // Padding within a framed rectangle (used by most widgets)
	_style.FrameRounding = 0.0f;                                // Radius of frame corners rounding. Set to 0.0f to have rectangular frames (used by most widgets).
	_style.ItemSpacing = ImVec2(5, 5);                        // Horizontal and vertical spacing between widgets/lines
	_style.ItemInnerSpacing = ImVec2(4, 4);                        // Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label)
	_style.TouchExtraPadding = ImVec2(0, 0);                        // Expand reactive bounding box for touch-based system where touch position is not accurate enough. Unfortunately we don't sort widgets so priority on overlap will always be given to the first widget. So don't grow this too much!
	_style.IndentSpacing = 21.0f;                               // Horizontal spacing when e.g. entering a tree node. Generally == (FontSize + FramePadding.x*2).
	_style.ColumnsMinSpacing = 6.0f;                                // Minimum horizontal spacing between two columns
	_style.ScrollbarSize = 16.0f;                               // Width of the vertical scrollbar, Height of the horizontal scrollbar
	_style.ScrollbarRounding = 9.0f;                                // Radius of grab corners rounding for scrollbar
	_style.GrabMinSize = 10.0f;                               // Minimum width/height of a grab box for slider/scrollbar
	_style.GrabRounding = 0.0f;                                // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
	_style.ButtonTextAlign = ImVec2(0.5f, 0.5f);                  // Alignment of button text when button is larger than text.
	_style.DisplayWindowPadding = ImVec2(22, 22);                      // Window positions are clamped to be IsVisible within the display area by at least this amount. Only covers regular windows.
	_style.DisplaySafeAreaPadding = ImVec2(4, 4);                        // If you cannot see the edge of your screen (e.g. on a TV) increase the safe area padding. Covers popups/tooltips as well regular windows.
	_style.AntiAliasedLines = true;                                // Enable anti-aliasing on lines/borders. Disable if you are really short on CPU/GPU.
	_style.AntiAliasedShapes = true;                                // Enable anti-aliasing on filled shapes (rounded rectangles, circles, etc.)
	_style.CurveTessellationTol = 1.25f;                               // Tessellation tolerance. Decrease for highly tessellated curves (higher quality, more polygons), increase to reduce quality.

	_style.Colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
	_style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	_style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
	_style.Colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.5f);			// 1.00f
	_style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.00f);
	_style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.90f);
	_style.Colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
	_style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	_style.Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	_style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.80f, 0.80f, 0.40f);
	_style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.90f, 0.65f, 0.65f, 0.45f);
	_style.Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	_style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	_style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	//_style.Colors[ImGuiCol_TitleText] = ImVec4(0.80f, 0.80f, 1.00f, 1.00f);
	_style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.40f, 0.40f, 0.55f, 0.80f);
	_style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
	_style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.40f, 0.40f, 0.80f, 0.30f);
	_style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.80f, 0.40f);
	_style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.80f, 0.50f, 0.50f, 0.40f);
	_style.Colors[ImGuiCol_ComboBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.99f);
	_style.Colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 0.60f, 0.90f, 0.50f);
	_style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
	_style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
	_style.Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.10f, 0.10f, 0.8f);				// 1.00f
	_style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.40f, 0.00f, 0.00f, 1.00f);
	_style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.70f, 0.20f, 0.00f, 0.83f);
	_style.Colors[ImGuiCol_Header] = ImVec4(0.40f, 0.40f, 0.90f, 0.45f);
	_style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.45f, 0.45f, 0.90f, 0.80f);
	_style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.53f, 0.53f, 0.87f, 0.80f);
	_style.Colors[ImGuiCol_Column] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	_style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.70f, 0.60f, 0.60f, 1.00f);
	_style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.90f, 0.70f, 0.70f, 1.00f);
	_style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
	_style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
	_style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
	_style.Colors[ImGuiCol_CloseButton] = ImVec4(0.10f, 0.10f, 0.10f, 0.50f);
	_style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.00f, 0.00f, 1.00f);
	_style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.70f, 0.20f, 0.00f, 0.83f);
	_style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	_style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	_style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	_style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	_style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}