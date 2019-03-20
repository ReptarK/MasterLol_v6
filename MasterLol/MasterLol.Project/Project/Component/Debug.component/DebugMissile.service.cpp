#include "DebugMissile.service.h"

#include <SDK/Game.h>

#include <Common/ObjectHelper.h>

void DebugMissileService::OnUpdate()
{

}

void ProcessMissile(MissileClient* missile)
{
	//__try {
	Obj_AI_Base* caster = (Obj_AI_Base*)Common::ObjectHelper::GetSourceObject(missile);

	if (!caster) return;
	if (!caster->IsHero()) return;



	auto spellInfo = missile->GetMissileSpellInfo();
	if (!spellInfo) return;
	auto spellData = spellInfo->GetSpellData();
	if (!spellData) return;

	printf("ProcessMissile :\n"\
		"\t-Caster ( %#x ) : %s\n"\
		"\t-Missile ( %#x ) : %s\n"\
		"\t\t-Time : %d\n",
		caster, caster->GetAIName().c_str(),
		missile, spellData->MissileName,
		missile->GetCreatedTimeMs());
	//while (!GetAsyncKeyState(VK_HOME));

	Draw.CircleFilled(missile->GetPos(), 40, WHITE_A(50));
	Draw.Line(missile->GetLaunchPosition(), missile->GetEndPosition(), (int)spellData->MissileWidth, RED_A(50));
	//}
	//__except (1) { return; };

}

void DebugMissileService::OnEndScene()
{
	if (!Option::Get().show_debug_missile)
		return;

	auto allMissile = Common::ObjectList::mAllMissiles;
	for (auto missile : allMissile)
	{
		ProcessMissile(missile);
	}
}

void DebugMissileService::OnCreateMissile(MissileClient * missile, Obj_AI_Base * caster)
{
	if (!Option::Get().log_missile)
		return;

	//if (caster && caster->IsHero()) {
	//	printf("OnMissileProcessSpell :\n\t-Caster (%#x) %s\n\t-Missile (%#x) : %s\n\n",
	//		caster, caster->GetAIName().c_str(), missile, missile->GetMissileSpellInfo()->GetSpellData()->MissileName);
	// }
	auto spellInfo = missile->GetMissileSpellInfo();
	if (!spellInfo) return;
	auto spellData = spellInfo->GetSpellData();
	if (!spellData) return;

	printf("ProcessMissile :\n"\
		"\t-Caster ( %#x ) : %s\n"\
		"\t-Missile ( %#x ) : %s\n"\
		"\t\t-Time : %d\n",
		caster, caster->GetAIName().c_str(),
		missile, spellData->MissileName,
		missile->GetCreatedTimeMs());
}