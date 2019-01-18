#include "GameFunctions.h"
#include <SDK/ObjectManager.h>

bool GameFunctions::IssueOrder( GameObject* player, GameObjectOrder order, Vector3* position,
	GameObject* targetObj, DWORD attackLoc, DWORD isPassive, uint networkID )
{
	static _fnIssueOrder oIssueOrder = ( _fnIssueOrder )( Patchables::LolBase + fnIssueOrder );

	if ( !player ) return false;

	oIssueOrder( player, order, position, targetObj, attackLoc, isPassive, targetObj ? *targetObj->GetNetworkId() : 0 );

	return true;
}

bool GameFunctions::IssueOrder( Vector3 & position, GameObjectOrder order, GameObject * targetObject )
{
	auto localPlayer = ObjectManager::GetPlayer();


	// Return False if trying to attack target
	// and unit is nullptr
	if ( order == GameObjectOrder::AttackUnit
		&& targetObject == nullptr )
	{
		return false;
	}

	DWORD issueOrderFlags1 = 0x0000000;
	DWORD issueOrderFlags2 = 0x0000000;

	switch ( order )
	{
	case GameObjectOrder::HoldPosition:
		oIssueOrder( player, GameObjectOrder::Stop, position, nullptr, 0, 0, 0x0000001 );

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
}
