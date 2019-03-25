#pragma once
#include "../IGameService.h"

class DebugNavigationService : public IGameService {

	void DrawNavigation(Obj_AI_Base* unit);

public:
	DebugNavigationService() {
	}

	virtual void OnUpdate();
	virtual void OnEndScene();
};
