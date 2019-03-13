#include "DebugMissile.service.h"

#include <SDK/Game.h>

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

		printf("Missile %#x (%d) casted by %#x\n", missile, missile->GetCreatedTimeMs() * 1000, caster);

		auto spellData = missile->GetMissileSpellInfo()->GetSpellData();
		if (!spellData) return;

		Draw.CircleFilled(missile->GetPos(), 40, WHITE());
		Draw.Line(*missile->GetLaunchPos(), *missile->GetDestPos(), 2, RED());
	}
	__except (1) { return; };

}

void DebugMissileService::OnEndScene()
{
	if (!Option::Get().enable_draw_debug_missile)
		return;

	auto allMissile = Common::ObjectList::mAllMissiles;
	for (auto missile : allMissile)
	{
		ProcessMissile(missile);
	}
}

void DebugMissileService::OnMissileProcessSpell(MissileClient * missile, Obj_AI_Base * caster)
{
	if (!Option::Get().enable_log_debug_hero_missile)
		return;

	if (caster && caster->IsHero()) {
		printf("OnMissileProcessSpell :\n\t-Caster (%#x) %s\n\t-Missile (%#x) : %s\n\n",
			caster, "caster->GetAIName()", missile, missile->GetMissileSpellInfo()->GetSpellData()->MissileName);
		//Game::PrintChat("Caster (%#x) %s : Missile (%#x) : %s\n", BLUE(),
		//	caster, caster->GetAIName(), missile, missile->GetMissileSpellInfo()->GetSpellData()->MissileName);
	}
}
