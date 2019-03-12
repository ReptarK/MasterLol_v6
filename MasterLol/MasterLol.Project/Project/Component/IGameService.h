#pragma once
#include "../Option.h"

#include <SDK/Inputs.h>
#include <SDK/Draw.h>

class IGameService {

public:
	virtual void OnUpdate() {}
	virtual void OnEndScene() {}
};
