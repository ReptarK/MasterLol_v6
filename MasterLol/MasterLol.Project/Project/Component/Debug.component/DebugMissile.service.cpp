#include "DebugMissile.service.h"

#include <Common/ObjectHelper.h>

void DebugMissileService::OnUpdate()
{

}

void ProcessMissile(MissileClient* missile) 
{
	__try {
		Obj_AI_Base* caster = (Obj_AI_Base*)Common::ObjectHelper::GetSourceObject(missile);

		if (!caster) return;
		if (!caster->IsHero()) return;

		printf("Missile %#x casted by %#x", missile, caster);
		Sleep(250);
		while (!GetAsyncKeyState(VK_HOME));

		auto spellData = missile->GetMissileSpellInfo()->GetSpellData();
		if (!spellData) return;

		Draw.CircleFilled(missile->GetPos(), 40, WHITE());
		Draw.Line(*missile->GetLaunchPos(), *missile->GetDestPos(), spellData->MissileWidth, RED());
	}
	__except (1) { return; };

}

void DebugMissileService::OnEndScene()
{
	auto allMissile = Common::ObjectList::mAllMissiles;
	for (auto missile : allMissile)
	{
		ProcessMissile(missile);
	}
}
