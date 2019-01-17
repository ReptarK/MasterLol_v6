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

bool AttackableUnit::IsAlive()
{
	typedef bool( __thiscall* _fnIsAlive )( GameObject* pObj );
	static _fnIsAlive oIsAlive = ( _fnIsAlive )( Patchables::LolBase + fnIsAlive );
	return oIsAlive( this );
}

bool AttackableUnit::IsTargetable()
{
	typedef bool( __thiscall* _fnIsTargetable )( GameObject* pObj );
	static _fnIsTargetable oIsTargetable = ( _fnIsTargetable )( Patchables::LolBase + fnIsTargetable );
	return oIsTargetable( this );
}

bool AttackableUnit::IsCaracterState( CaracterState state )
{
	return CHECK_BIT( *GetCaracterState(), ( int )state );
}

bool AttackableUnit::IsStunned()
{
	return !IsCaracterState( CaracterState::CanAttack ) && !IsCaracterState( CaracterState::CanMove );
}

float AttackableUnit::GetHealthPercent()
{
	if ( !this || !this->IsAlive() ) return 0;

	return *this->GetHealth() * 100 / *this->GetMaxHealth();
}

float AttackableUnit::GetManaPercent()
{
	if ( !this || !this->IsAlive() ) return 0;

	return *this->GetMana() * 100 / *this->GetMaxMana();
}


