#pragma once
#include "../IGameService.h"

class ClearLogicService : public IGameService {

	const int ACTIVE_KEY = 0x56; // V key

	virtual void OnUpdate();
};
