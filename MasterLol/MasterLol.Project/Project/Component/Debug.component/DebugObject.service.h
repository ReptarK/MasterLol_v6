#pragma once
#include "../IGameService.h"
#include <SDK/GameObject.h>

class DebugObjectService : public IGameService {
public:
	DebugObjectService() {
	}

	virtual void OnEndScene();
};
