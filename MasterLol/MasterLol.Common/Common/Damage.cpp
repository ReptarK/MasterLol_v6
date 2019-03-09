#include "Damage.h"

namespace Common
{
	float Damage::TotalAttackDamage( Obj_AI_Base * from )
	{
		return from->GetUnitStats()->mFlatPhysicalDamageMod + from->GetUnitStats()->mBaseAttackDamage;
	}
	float Damage::TotalMagicalDamage( Obj_AI_Base * from )
	{
		return from->GetUnitStats()->mFlatMagicDamageMod + from->GetUnitStats()->mBaseAbilityDamage;
	}

	float Damage::GetCriticalStrikePercentMod( Obj_AI_Base * from )
	{
		// TO DO :
		return 0.5f;
	}

	PrecalculatedAutoAttackDamage Damage::GetStaticAutoAttackDamage( Obj_AI_Base* from, bool targetIsMinion )
	{
		auto precalculated = PrecalculatedAutoAttackDamage();
		precalculated._rawTotal = TotalAttackDamage( from );

		return precalculated;
	}
	float Damage::GetAutoAttackDamage( Obj_AI_Base * target, PrecalculatedAutoAttackDamage precalculated, Obj_AI_Base * from )
	{
		auto targetIsMinion = target->IsMinion();
		auto calculatedPhysicalDamage = precalculated._calculatedPhysical;
		auto calculatedMagicalDamage = precalculated._calculatedMagical;
		auto calculatedTrueDamage = precalculated._calculatedTrue;
		auto rawPhysicalDamage = precalculated._rawPhysical;
		auto rawMagicalDamage = precalculated._rawMagical;
		auto rawTotal = precalculated._rawTotal;
		auto guaranteedCriticalStrike = false;

		if ( targetIsMinion && *target->GetMaxHealth() >= 0 && *target->GetMaxHealth() <= 6 )
			return 1;

		switch ( precalculated._autoAttackDamageType )
		{
		case ESpellDamageType::Physical:
			rawPhysicalDamage += rawTotal;
			break;
		case ESpellDamageType::Magical:
			rawMagicalDamage += rawTotal;
			break;
		case ESpellDamageType::True:
			calculatedTrueDamage += rawTotal;
			break;
		}

		if ( rawPhysicalDamage > 0.0f )
		{
			calculatedPhysicalDamage += CalculateDamageOnUnit( from, target, ESpellDamageType::Physical, rawPhysicalDamage,
				false, precalculated._autoAttackDamageType == ESpellDamageType::Physical );
		}
		if ( rawMagicalDamage > 0.0f )
		{
			calculatedMagicalDamage += CalculateDamageOnUnit( from, target, ESpellDamageType::Magical, rawMagicalDamage,
				false, precalculated._autoAttackDamageType == ESpellDamageType::Magical );
		}
		auto percentMod = 1.0f;
		if ( std::abs( from->GetUnitStats()->mCrit - 1.0f ) < FLT_EPSILON || guaranteedCriticalStrike )
		{
			percentMod *= GetCriticalStrikePercentMod( from );
		}
		return ( percentMod * calculatedPhysicalDamage ) + calculatedMagicalDamage + calculatedTrueDamage;
	}
	float Damage::CalculateDamageOnUnit(
		Obj_AI_Base * from,
		Obj_AI_Base * target,
		ESpellDamageType::ESpellDamageType damageType,
		float rawDamage,
		bool isAbility, bool isAutoAttackOrTargetted )
	{
		if ( target == nullptr )
		{
			return 0.0f;
		}

		auto percentMod = 1.0f;
		auto baseResistance = 0.0f;
		auto bonusResistance = 0.0f;
		auto reductionFlat = 0.0f;
		auto reductionPercent = 0.0f;
		auto penetrationFlat = 0.0f;
		auto penetrationPercent = 0.0f;
		auto bonusPenetrationPercent = 0.0f;

		switch ( damageType )
		{
		case ESpellDamageType::Physical:
			baseResistance = target->GetUnitStats()->mArmor;
			bonusResistance = target->GetUnitStats()->mBonusArmor;
			if ( from->IsMinion() )
			{
				penetrationFlat = 0.0f;
				penetrationPercent = 0.0f;
				bonusPenetrationPercent = 0.0f;
			}
			// Turrets passive.
			else if ( from->IsTurret() )
			{
				penetrationFlat = 0.0f;
				//penetrationPercent = from.IsLaneTurret() ? 0.75f : 0.25f;
				bonusPenetrationPercent = 0.0f;
			}
			break;
		case ESpellDamageType::Magical:
			baseResistance = target->GetUnitStats()->mMagicResist;
			bonusResistance = target->GetUnitStats()->mBonusMagicResist;
			break;

		case ESpellDamageType::True:
			return rawDamage;
		}

		auto resistance = baseResistance + bonusResistance;
		if ( resistance > 0 )
		{
			auto basePercent = baseResistance / resistance;
			auto bonusPercent = 1.0f - basePercent;
			baseResistance -= reductionFlat * basePercent;
			bonusResistance -= reductionFlat * bonusPercent;
			resistance = baseResistance + bonusResistance;
			if ( resistance > 0 )
			{
				baseResistance *= 1.0f - reductionPercent;
				bonusResistance *= 1.0f - reductionPercent;
				baseResistance *= 1.0f - penetrationPercent;
				bonusResistance *= 1.0f - penetrationPercent;
				bonusResistance *= 1.0f - bonusPenetrationPercent;
				resistance = baseResistance + bonusResistance;
				resistance -= penetrationFlat;
			}
		}
		// Penetration cant reduce resistance below 0.
		if ( resistance >= 0 )
		{
			percentMod *= 100.0f / ( 100.0f + resistance );
		}
		else
		{
			percentMod *= 2.0f - 100.0f / ( 100.0f - resistance );
		}

		if ( percentMod * rawDamage > 0 )
			return percentMod * rawDamage;
		return 0;
	}
	float Damage::GetDamageSpell( Obj_AI_Base * source, Obj_AI_Base * target, ESpellSlot::ESpellSlot slot )
	{
		return 0.0f;
	}
}
