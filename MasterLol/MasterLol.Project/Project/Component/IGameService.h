#pragma once
#include "../Menu/MenuTab.h"

class IGameService: public MenuTab {
public:
	virtual void RenderMenu();

	virtual void OnUpdate();
	virtual void OnEndScene();
};
