#pragma once
#include <d3d9.h>
#include <string>

#define StartColor			D3DCOLOR_ARGB(255, 33, 33, 33)
#define EndColor			D3DCOLOR_ARGB(255, 20, 20, 20)
#define BorderColor			D3DCOLOR_ARGB(255, 0, 0, 0)
#define SelectionColor		D3DCOLOR_ARGB(255, 13, 13, 13)
#define OffColor			D3DCOLOR_ARGB(255, 135, 135, 135)
#define ColorOffset			D3DCOLOR_ARGB(0, 25, 25, 25)

#include <SDK/EventManager.h>
#include <SDK/imGui/imgui.h>
#include "../Component/ComponentsManager.h"

class Menu
{
	static void OnEndScene(LPDIRECT3DDEVICE9 device);
	static void OnReset(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);

public:
	static void Initialize();
	static void Shutdown();

	static void OnDeviceLost();
	static void OnDeviceReset();

	static bool IsVisible() { return _isVisible; }
	static void Toggle() { _isVisible = !_isVisible; }

private:
	static ImVec2 GetSidebarSize();
	static void CreateStyle();
	static void RenderTabs(int& activetab, float w, float h, bool sameline);

	static ImGuiStyle _style;
	static bool _isVisible;
};
