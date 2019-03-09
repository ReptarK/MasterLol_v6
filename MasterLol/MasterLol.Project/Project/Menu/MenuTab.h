#pragma once
#include <SDK/Options.h>

#include <SDK/imGui/imgui_impl_dx9.h>
#include <SDK/ImGui/imgui.h>
#include <SDK/ImGui/imgui_internal.h>

class MenuTab {
public:
	bool mIsActive;
	const char* mName;

	MenuTab(const char* name) {
		mIsActive = false;
		mName = name;
	}

	virtual void Render() {}

	static void Start(int nbColumns);

	static void End() { ImGui::PopStyleVar(); }
};

// CUSTOM TABS

class VisualsTab : public MenuTab {
public:
	VisualsTab() : MenuTab("VISUALS") {}

	virtual void Render();
};

class CommonTab : public MenuTab {
public:
	CommonTab() : MenuTab("COMMON") {}

	virtual void Render();
};

class DebugTab : public MenuTab {
public:
	DebugTab() : MenuTab("DEBUG") {}

	virtual void Render();
};
