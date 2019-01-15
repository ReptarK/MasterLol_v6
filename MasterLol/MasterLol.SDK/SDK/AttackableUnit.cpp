#include "stdafx.h"
#include "AttackableUnit.h"

bool AttackableUnit::IsMelee()
{
	return *GetCombatType() == CombatType::Melee;
}

bool AttackableUnit::IsRanged()
{
	return *GetCombatType() == CombatType::Melee;
}

bool AttackableUnit::IsCaracterState(CaracterState state)
{
	return CHECK_BIT(*GetCaracterState(), (int)state);
}

bool AttackableUnit::IsStunned()
{
	return !IsCaracterState(CaracterState::CanAttack) && !IsCaracterState(CaracterState::CanMove);
}

float AttackableUnit::GetHealthPercent()
{
	if (!this
		|| *this->GetIsDead()
		|| *this->GetHealth() == 0) return 0;

	return *this->GetHealth() * 100 / *this->GetMaxHealth();
}

float AttackableUnit::GetManaPercent()
{
	if (!this
		|| *this->GetIsDead()
		|| *this->GetMana() == 0) return 0;

	return *this->GetMana() * 100 / *this->GetMaxMana();
}


