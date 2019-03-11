#pragma once
#include <SDK/imGui/imgui_impl_dx9.h>
#include <SDK/ImGui/imgui.h>
#include <SDK/ImGui/imgui_internal.h>
#include <SDK/Options.h>

class IGameService {
public:
	virtual void RenderMenu() {}

	virtual void OnUpdate() {}
	virtual void OnEndScene() {}
};
