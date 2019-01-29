#include "GameFunctions.h"
#include <SDK/ObjectManager.h>
#include <SDK/AIHeroClient.h>
#include <SDK/Spellbook.h>

// IssueOrder
bool GameFunctions::IssueOrder( GameObject* player, EGameObjectOrder order, Vector3* position,
	GameObject* targetObj, DWORD attackLoc, DWORD isPassive, uint networkID )
{
	static _fnIssueOrder oIssueOrder = ( _fnIssueOrder )( Patchables::LolBase + fnIssueOrder );

	if ( !player ) return false;

	oIssueOrder( player, order, position, targetObj, attackLoc, isPassive, networkID );

	return true;
}

bool GameFunctions::IssueOrder( Vector3 position, EGameObjectOrder order, GameObject * targetObject )
{
	auto localPlayer = ObjectManager::GetPlayer();
	if ( !localPlayer ) return false;

	// Return False if trying to attack target
	// and unit is nullptr
	if ( order == EGameObjectOrder::AttackUnit
		&& targetObject == nullptr )
	{
		return false;
	}

	DWORD issueOrderFlags1 = 0x0000000;
	DWORD issueOrderFlags2 = 0x0000000;

	switch ( order )
	{
	case EGameObjectOrder::HoldPosition:
		GameFunctions::IssueOrder( ( GameObject* )localPlayer, EGameObjectOrder::Stop,
			&position, nullptr, 0, 0, 0x0000001 );

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

	GameFunctions::IssueOrder( ( GameObject* )localPlayer, order, &position, targetObject,
		issueOrderFlags1, issueOrderFlags2, targetObject ? *targetObject->GetNetworkId() : 0 );

	return true;
}

// SPELLS
bool GameFunctions::CastSpell( ESpellSlot::ESpellSlot slot, Vector3 dstPosition, Vector3 srcPosition, uint targetNetworkID )
{
	auto localPlayer = ObjectManager::GetPlayer();
	if ( !localPlayer ) return false;

	localPlayer->GetSpellbook()->CastSpell( slot, dstPosition, srcPosition, targetNetworkID );
	return true;
}

bool GameFunctions::CastSpell( ESpellSlot::ESpellSlot slot, GameObject * targetObject )
{
	return GameFunctions::CastSpell(slot, targetObject->GetPos(), Vector3(0,0,0), *targetObject->GetNetworkId());
}

bool GameFunctions::UpdateChargeableSpell( ESpellSlot::ESpellSlot slot, Vector3 position, bool releaseCast )
{
	auto localPlayer = ObjectManager::GetPlayer();
	if ( !localPlayer ) return false;

	localPlayer->GetSpellbook()->UpdateChargeableSpell( slot, position, releaseCast );
	return true;
}

ESpellState GameFunctions::GetSpellState( ESpellSlot::ESpellSlot slot )
{
	auto localPlayer = ObjectManager::GetPlayer();
	if ( !localPlayer ) return ESpellState::NotAvailable;

	return localPlayer->GetSpellbook()->GetSpellState( slot );
}
