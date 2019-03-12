#include "DebugCollision.service.h"

#include <SDK/HudManager.h>
#include <SDK/Game.h>
#include <SDK/Obj_AI_Base.h>

#include <Common/Geometry/LineCollision.h>
#include <Common/Geometry/CircleCollision.h>
#include <Common/Damage.h>
#include <Common/ObjectHelper.h>

void DebugCollisionService::OnUpdate()
{
	if (Option::Get().enable_debug_collision)
	{
		// Left click to select a Target
		if (GetAsyncKeyState(VK_LBUTTON) & 1)
			this->mSelectedTarget = HudManager::GetUnderMouseObject();

		// Right click to unselect Target
		if (GetAsyncKeyState(VK_RBUTTON) & 1)
			this->mSelectedTarget = nullptr;
	}
}

void DebugCollisionService::OnEndScene()
{
	if (Option::Get().enable_debug_collision)
	{
		AIHeroClient* player = ObjectManager::GetPlayer();
		Vector3 sourcePos = player->GetPos();
		Vector3 mousePos = HudManager::GetGameCursor()->Position;
		Geometry::LineCollision line = Geometry::LineCollision(sourcePos, mousePos, this->LINE_COLLISION_WIDTH);

		if (this->mSelectedTarget)
		{
			Draw.RangeCircle(this->mSelectedTarget->GetPos(), this->mSelectedTarget->GetBoundingRadius(), YELLOW(), 1);

			bool isCollision = line.IsCollision(Geometry::Circle3D(this->mSelectedTarget->GetPos(), this->mSelectedTarget->GetBoundingRadius()));
			Draw.Line(sourcePos, mousePos, this->LINE_COLLISION_WIDTH, isCollision ? RED() : BLUE());
		}
		else
			Draw.Line(sourcePos, mousePos, this->LINE_COLLISION_WIDTH, BLUE());
	}
}
