#include "DebugComponent.h"
#include <SDK/EventManager.h>
#include <SDK/HudManager.h>
#include <SDK/Game.h>
#include <SDK/Obj_AI_Base.h>
#include <SDK/Options.h>

#include <Common/Geometry/LineCollision.h>
#include <Common/Geometry/CircleCollision.h>
#include <Common/Damage.h>
#include <Common/ObjectHelper.h>

GameObject * DebugComponent::selectedtarget = nullptr;

void DebugComponent::Initialize()
{
	EventHandler<EventIndex::OnDrawingEndScene, EventDefines::OnDrawingEndScene, IDirect3DDevice9*>::GetInstance()->Add(DebugComponent::OnEndScene);
	EventHandler<EventIndex::OnMainLoop, EventDefines::OnMainLoop>::GetInstance()->Add(DebugComponent::OnUpdate);
}

void DebugComponent::OnUpdate()
{
	if (g_Options.enable_debug_collision)
	{
		// Left click to select a Target
		if (GetAsyncKeyState(VK_LBUTTON) & 1)
			selectedtarget = HudManager::GetUnderMouseObject();

		// Right click to unselect Target
		if (GetAsyncKeyState(VK_RBUTTON) & 1)
			selectedtarget = nullptr;
	}
}

void DebugComponent::OnEndScene(IDirect3DDevice9* device)
{
	if (g_Options.enable_debug_collision)
	{
		AIHeroClient* player = ObjectManager::GetPlayer();
		Vector3 sourcePos = player->GetPos();
		Vector3 mousePos = HudManager::GetGameCursor()->Position;
		Geometry::LineCollision line = Geometry::LineCollision(sourcePos, mousePos, LINE_WIDTH);

		if (selectedtarget)
		{
			Draw.RangeCircle(selectedtarget->GetPos(), selectedtarget->GetBoundingRadius(), YELLOW(), 1);

			bool isCollision = line.IsCollision(Geometry::Circle3D(selectedtarget->GetPos(), selectedtarget->GetBoundingRadius()));
			isCollision ? Draw.Line(sourcePos, mousePos, LINE_WIDTH, RED()) : Draw.Line(sourcePos, mousePos, LINE_WIDTH, BLUE());
		}
		else
			Draw.Line(sourcePos, mousePos, LINE_WIDTH, BLUE());
	}

	if (g_Options.show_lasthit_targets)
	{
		auto AARange = ObjectManager::GetPlayer()->GetUnitStats()->mAttackRange;
		auto AADamage = Common::Damage::GetStaticAutoAttackDamage();

		ObjectIterator it = ObjectIterator();
		while (!it.End())
		{
			Obj_AI_Base* currObject = (Obj_AI_Base*)it.Next();

			if (!currObject->IsMinion()) continue;
			if (!Common::ObjectHelper::IsValidTarget(currObject, AARange))continue;

			auto damageOnTarget = Common::Damage::GetAutoAttackDamage(currObject, AADamage);
			if (*currObject->GetHealth() < damageOnTarget) {
				Draw.CircleFilled(currObject->GetPos(), currObject->GetBoundingRadius() / 2, GREEN());
			}
		}
	}
}
