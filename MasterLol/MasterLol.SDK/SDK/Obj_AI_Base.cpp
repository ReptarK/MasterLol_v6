#include "stdafx.h"
#include "Obj_AI_Base.h"
#include "Spellbook.h"
#include "SpellCastInfo.h"
#include "EventManager.h"
#include "Names.h"

AIManager * Obj_AI_Base::GetAIManager()
{
	return this->GetVirtual()->GetAIManager();
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

using _fnIssueOrder = void( __thiscall* )( GameObject* Player, GameObjectOrder dwOrder, Vector3* TargetPos,
	GameObject* TargetPtr, DWORD attackLoc, DWORD isPassive, uint NetWorkId );

bool Obj_AI_Base::IssueOrder( Vector3 position, GameObjectOrder order, GameObject* unit )
{
	Vector3* pPosition = new Vector3( position.x, position.y, position.z );
	_fnIssueOrder originalIssueOrder = ( _fnIssueOrder )( Patchables::LolBase + fnIssueOrder );

	if ( pPosition == nullptr || this == nullptr )
	{
		return false;
	}

	// Return False if trying to attack target
	// and unit is nullptr
	if ( order == GameObjectOrder::AttackUnit
		&& unit == nullptr )
	{
		return false;
	}

	DWORD issueOrderFlags1 = 0x0000000;
	DWORD issueOrderFlags2 = 0x0000000;

	switch ( order )
	{
	case GameObjectOrder::HoldPosition:
		//originalIssueOrder(GameObjectOrder::Stop, position, nullptr, 0, 0, 0x0000001);
		originalIssueOrder( this, GameObjectOrder::Stop, pPosition, nullptr, 0, 0, 0x0000001 );

		issueOrderFlags1 = 0x0000000;
		issueOrderFlags2 = 0x0000001;
		break;
	case GameObjectOrder::MoveTo:
		break;
	case GameObjectOrder::AttackTo:
	case GameObjectOrder::AttackUnit:
	case GameObjectOrder::AutoAttack:
	case GameObjectOrder::AutoAttackPet:
		issueOrderFlags1 = 0xffffff00;
		break;
	case GameObjectOrder::Stop:
		issueOrderFlags2 = 0x0000001;
		break;
	case GameObjectOrder::MovePet:
		break;
	}

	originalIssueOrder( this, order, pPosition, unit, issueOrderFlags1, issueOrderFlags2, unit ? *unit->GetNetworkId() : 0 );

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



