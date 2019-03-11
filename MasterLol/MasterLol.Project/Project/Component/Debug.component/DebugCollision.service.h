#pragma once
#include "../IGameService.h"
#include <SDK/GameObject.h>

class DebugCollisionService : public IGameService {
public:
	const float LINE_COLLISION_WIDTH = 55;

	GameObject* mSelectedTarget;

	DebugCollisionService() {
		this->mSelectedTarget = nullptr;
	}

	virtual void OnUpdate();
	virtual void OnEndScene();
};
