#pragma once
#include "../IGameService.h"
#include "IOrbwalker.h"

class ClearLogicService : public IGameService, public IOrbwalker {

	const int ACTIVE_KEY = 0x56; // V key

	bool IsValidTarget(Obj_AI_Base * unit);
	Obj_AI_Base* FindBestTarget();

public:
	virtual void OnUpdate();
};
