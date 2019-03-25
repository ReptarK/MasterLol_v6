#include "FleeLogic.service.h"
#include "Orbwalker.component.h"

#include <SDK/HudManager.h>
#include <SDK/Inputs.h>

#include <Common/GameFunctions.h>

void FleeLogicService::OnUpdate()
{
	// X key
	if (InputSys::Get().IsKeyDown(this->ACTIVE_KEY) && TimerService::Get().CanMove()) {
		GameFunctions::IssueOrder(HudManager::GetGameCursor()->Position, EGameObjectOrder::MoveTo);
	}
}
