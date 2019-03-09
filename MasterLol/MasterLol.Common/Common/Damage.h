#pragma once
#include <SDK/StaticEnums.h>
#include <SDK/ObjectManager.h>
#include <SDK/AIHeroClient.h>

namespace Common
{
	struct PrecalculatedAutoAttackDamage
	{
		float _rawTotal;
		float _rawPhysical;
		float _rawMagical;
		float _calculatedPhysical;
		float _calculatedMagical;
		float _calculatedTrue;
		ESpellDamageType::ESpellDamageType _autoAttackDamageType = ESpellDamageType::Physical;
	};

	class Damage
	{
	public:
		static float TotalAttackDamage( Obj_AI_Base* from );
		static float TotalMagicalDamage( Obj_AI_Base* from );
		static float GetCriticalStrikePercentMod( Obj_AI_Base* from );

		static PrecalculatedAutoAttackDamage GetStaticAutoAttackDamage( Obj_AI_Base* from = ObjectManager::GetPlayer(), bool targetIsMinion = true );

		static float GetAutoAttackDamage( Obj_AI_Base* target, PrecalculatedAutoAttackDamage precalculated, Obj_AI_Base* from = ObjectManager::GetPlayer() );

		static float CalculateDamageOnUnit(
			Obj_AI_Base* from,
			Obj_AI_Base* target,
			ESpellDamageType::ESpellDamageType,
			float rawDamage,
			bool isAbility = false,
			bool isAutoAttackOrTargetted = false 
		);

		static float GetDamageSpell(
			Obj_AI_Base* source,
			Obj_AI_Base* target,
			ESpellSlot::ESpellSlot slot
		);
	};
}

