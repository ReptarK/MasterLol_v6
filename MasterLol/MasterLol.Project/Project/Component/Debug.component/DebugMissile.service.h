#pragma once
#include "../IGameService.h"

class DebugMissileService : public IGameService {
public:
	DebugMissileService() {
	}

	virtual void OnUpdate();
	virtual void OnEndScene();
	virtual void OnCreateMissile(MissileClient*, Obj_AI_Base*);

};