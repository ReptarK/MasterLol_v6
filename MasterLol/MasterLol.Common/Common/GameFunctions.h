#pragma once
#include <SDK/GameObject.h>
#include <SDK/StaticEnums.h>

class GameFunctions
{
	// IssueOrder
	using _fnIssueOrder = void( __thiscall* )( GameObject* player, GameObjectOrder order, Vector3* position,
		GameObject* targetObj, DWORD attackLoc, DWORD isPassive, uint networkID );

	bool IssueOrder( GameObject* player, GameObjectOrder order, Vector3* position,
		GameObject* targetObj, DWORD attackLoc, DWORD isPassive, uint networkID );

	bool IssueOrder( Vector3 & position, GameObjectOrder order, GameObject * targetObject );
};