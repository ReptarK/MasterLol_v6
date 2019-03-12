#include "FleeLogic.service.h"

#include <SDK/HudManager.h>

#include <Common/GameFunctions.h>

void FleeLogicService::OnUpdate()
{
	// X key
	if (GetAsyncKeyState(this->ACTIVE_KEY)) {
		GameFunctions::IssueOrder(HudManager::GetGameCursor()->Position, EGameObjectOrder::MoveTo);
	}
}
