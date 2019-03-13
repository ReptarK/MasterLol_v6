#pragma once
#include "../IGameService.h"

class TimerService : public IGameService {

public:
	float mLastAttackTime;

	virtual void OnUpdate();
};

