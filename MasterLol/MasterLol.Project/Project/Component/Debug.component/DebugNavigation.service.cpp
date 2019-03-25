#include "DebugNavigation.service.h"

#include <Common/ObjectHelper.h>

#include <SDK/AIHeroClient.h>
#include <SDK/Navigation.h>

void DebugNavigationService::DrawNavigation(Obj_AI_Base * unit)
{
	if (!unit || !unit->IsAlive())
		return;

	Navigation* navigation = unit->GetNavigation();
	if (!navigation->mIsMoving) 
		return;

	PathManager pathManager = navigation->mPathManager;
	Vector3 lastWaypoint = unit->GetPos();
	int size = pathManager.GetSize();
	for (int i = pathManager.mCurrentPathId; i < size; ++i) {
		Draw.Line(lastWaypoint, pathManager.mPath[i], 2, WHITE_A(50));
		lastWaypoint = pathManager.mPath[i];
	}
}

void DebugNavigationService::OnUpdate()
{
}

void DebugNavigationService::OnEndScene()
{
	if (!Option::Get().enable_debug_navigation)
		return;

	auto allHero = Common::ObjectList::mAllHeros;
	for (Obj_AI_Base* unit : allHero)
	{
		DrawNavigation(unit);
	}

	auto allMinion = Common::ObjectList::mAllMinions;
	for (Obj_AI_Base* unit : allMinion)
	{
		DrawNavigation(unit);
	}


}
