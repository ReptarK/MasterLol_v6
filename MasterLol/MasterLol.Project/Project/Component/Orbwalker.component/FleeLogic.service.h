#pragma once
#include "../IGameService.h"

class FleeLogicService : public IGameService {

	const int ACTIVE_KEY = 0x58; // X key

	virtual void OnUpdate();
};
