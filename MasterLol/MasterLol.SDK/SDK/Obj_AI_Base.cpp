#include "stdafx.h"
#include "Obj_AI_Base.h"
#include "Spellbook.h"
#include "SpellCastInfo.h"
#include "EventManager.h"
#include "Names.h"
#include "ObjectManager.h"
#include "Hooks.h"

MAKE_HOOK<convention_type::thiscall_r, int, Navigation*, int, DWORD*> OnFunction16_Hook;

int __fastcall OnFunction16( Navigation* navigation, void* edx, int a2, DWORD* a3 )
{
	printf( "Navigation* = %#x, int = %i, DWORD* = %#x", navigation, a2, a3 );
	return OnFunction16_Hook.CallOriginal( navigation, a2, a3 );
}

void Obj_AI_Base::ApplyHooks()
{
	//auto player = ObjectManager::GetPlayer();
	//DWORD** virtualTable = *( DWORD*** )player->GetNavigation();
	//DWORD* function16 = virtualTable[16];
	//printf( "Hooked function16 at : %#x \n", ( DWORD )function16 );
	//OnFunction16_Hook.Apply( ( DWORD )function16, OnFunction16 );
}

Navigation * Obj_AI_Base::GetNavigation()
{
	__try {
	return this->GetVirtual()->GetNavigation();

	}
	__except ( 1 ) { return 0; }
}

Spellbook * Obj_AI_Base::GetSpellbook()
{
	Spellbook* spellbook = ( Spellbook* )( this + ( int )Offsets::Obj_AI_Base::SpellBook );
	if ( !spellbook )
		return nullptr;

	return spellbook;
}

std::string Obj_AI_Base::GetAIName()
{
	if ( this == nullptr )
		return "Unknown";

	return reinterpret_cast< char* >( this + static_cast< int >( Offsets::Obj_AI_Base::AIName ) );
}

using _fnIssueOrder = void( __thiscall* )( GameObject* Player, EGameObjectOrder dwOrder, Vector3* TargetPos,
	GameObject* TargetPtr, DWORD attackLoc, DWORD isPassive, uint NetWorkId );

bool Obj_AI_Base::IssueOrder( Vector3 position, EGameObjectOrder order, GameObject* unit )
{
	_fnIssueOrder originalIssueOrder = ( _fnIssueOrder )( Patchables::LolBase + fnIssueOrder );

	if ( this == nullptr )
	{
		return false;
	}

	// Return False if trying to attack target
	// and unit is nullptr
	if ( order == EGameObjectOrder::AttackUnit
		&& unit == nullptr )
	{
		return false;
	}

	DWORD issueOrderFlags1 = 0x0000000;
	DWORD issueOrderFlags2 = 0x0000000;

	switch ( order )
	{
	case EGameObjectOrder::HoldPosition:
		//originalIssueOrder(GameObjectOrder::Stop, position, nullptr, 0, 0, 0x0000001);
		originalIssueOrder( this, EGameObjectOrder::Stop, &position, nullptr, 0, 0, 0x0000001 );

		issueOrderFlags1 = 0x0000000;
		issueOrderFlags2 = 0x0000001;
		break;
	case EGameObjectOrder::MoveTo:
		break;
	case EGameObjectOrder::AttackTo:
	case EGameObjectOrder::AttackUnit:
	case EGameObjectOrder::AutoAttack:
	case EGameObjectOrder::AutoAttackPet:
		issueOrderFlags1 = 0xffffff00;
		break;
	case EGameObjectOrder::Stop:
		issueOrderFlags2 = 0x0000001;
		break;
	case EGameObjectOrder::MovePet:
		break;
	}

	originalIssueOrder( this, order, &position, unit, issueOrderFlags1, issueOrderFlags2, unit ? *unit->GetNetworkId() : 0 );

	return true;
}

float Obj_AI_Base::GetAttackDelay()
{
	__try
	{
		float returnValue = 0.0f;

		typedef float( __cdecl* _fnGetAttackDelay )( GameObject* pObj, int index );
		_fnGetAttackDelay oGetAttackDelay = reinterpret_cast< _fnGetAttackDelay >( Patchables::LolBase + fnGetAttackDelay );

		returnValue = oGetAttackDelay( this, 64 );
		return returnValue /*/ AASpellModule*/;
	}
	__except ( 1 ) { return 0; }
}

float Obj_AI_Base::GetAttackCastDelay()
{
	__try
	{
		float returnValue = 0.0f;

		typedef float( __cdecl* _fnGetAttackCastDelay )( GameObject* pObj, int index );
		_fnGetAttackCastDelay oGetAttackCastDelay = reinterpret_cast< _fnGetAttackCastDelay >( Patchables::LolBase + fnGetAttackCastDelay );

		returnValue = oGetAttackCastDelay( this, 64 );

		return returnValue;
	}
	__except ( 1 ) { return 0; }
}



