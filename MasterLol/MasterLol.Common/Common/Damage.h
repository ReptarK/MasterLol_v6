#pragma once
#include <SDK/StaticEnums.h>
#include <SDK/ObjectManager.h>
#include <SDK/AIHeroClient.h>

namespace MasterLol
{
	struct PrecalculatedAutoAttackDamage
	{
		float _rawTotal;
		float _rawPhysical;
		float _rawMagical;
		float _calculatedPhysical;
		float _calculatedMagical;
		float _calculatedTrue;
		SpellDamageType::SpellDamageType _autoAttackDamageType = SpellDamageType::Physical;
	};

	class Damage
	{
	public:
		static float TotalAttackDamage(Obj_AI_Base* from);
		static float TotalMagicalDamage(Obj_AI_Base* from);
		static float GetCriticalStrikePercentMod(Obj_AI_Base* from);

		static PrecalculatedAutoAttackDamage GetStaticAutoAttackDamage(Obj_AI_Base* from = ObjectManager::Get().GetPlayer(), bool targetIsMinion = true);

		static float GetAutoAttackDamage(Obj_AI_Base* target, PrecalculatedAutoAttackDamage precalculated, Obj_AI_Base* from = ObjectManager::Get().GetPlayer());

		static float CalculateDamageOnUnit(
			Obj_AI_Base* from,
			Obj_AI_Base* target,
			SpellDamageType::SpellDamageType,
			float rawDamage,
			bool isAbility = false,
			bool isAutoAttackOrTargetted = false);
	};
}

