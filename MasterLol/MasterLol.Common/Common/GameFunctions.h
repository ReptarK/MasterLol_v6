#pragma once
#include <SDK/GameObject.h>
#include <SDK/StaticEnums.h>

class GameFunctions
{
public:
#pragma region ISSUE_ORDER

	using _fnIssueOrder = void( __thiscall* )( GameObject* player, EGameObjectOrder order, Vector3* position,
		GameObject* targetObj, DWORD attackLoc, DWORD isPassive, uint networkID );

	static bool IssueOrder( GameObject* player, EGameObjectOrder order, Vector3* position,
		GameObject* targetObj, DWORD attackLoc, DWORD isPassive, uint networkID );

	static bool IssueOrder( Vector3 position, EGameObjectOrder order, GameObject * targetObject = nullptr );

#pragma endregion


#pragma region SPELLS

	static bool CastSpell( ESpellSlot::ESpellSlot slot, Vector3 dstPosition, Vector3 srcPosition, uint targetNetworkID );

	static bool CastSpell( ESpellSlot::ESpellSlot slot, GameObject* targetObject );

	static bool UpdateChargeableSpell( ESpellSlot::ESpellSlot slot, Vector3 position, bool releaseCast );

	static ESpellState GetSpellState( ESpellSlot::ESpellSlot slot );

#pragma endregion

};