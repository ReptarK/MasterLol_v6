#include "stdafx.h"
#include "Obj_AI_Base.h"
#include "Spellbook.h"
#include "SpellCastInfo.h"
#include "EventManager.h"
#include "Names.h"

MAKE_HOOK<convention_type::thiscall_r, void, GameObject*, GameObjectOrder, Vector3*, GameObject*, DWORD, DWORD, uint> IssueOrder_Hook;
MAKE_HOOK<convention_type::thiscall_r, void, Spellbook*, SpellCastInfo*> OnProcessSpell_Hook;

void __fastcall OnIssueOrder(GameObject* Player, void *EDX, GameObjectOrder dwOrder, Vector3* TargetPos,
	GameObject* TargetPtr, DWORD attackLoc, DWORD isPassive, uint NetWorkId)
{
	EventHandler<EventIndex::OnObjAIBaseIssueOrder, EventDefines::OnObjAIBaseIssueOrder, GameObject*, GameObjectOrder, Vector3*, GameObject*, DWORD, DWORD, uint>::GetInstance()->
		TriggerProcess(Player, dwOrder, TargetPos, TargetPtr, attackLoc, isPassive, NetWorkId);
	IssueOrder_Hook.CallOriginal(Player, dwOrder, TargetPos, TargetPtr, attackLoc, isPassive, NetWorkId);
}

void __fastcall OnProcessSpell(Spellbook* spellBook, void* edx, SpellCastInfo* spellCastInfo)
{
	EventHandler<EventIndex::OnObjAIBaseProcessSpell, EventDefines::OnObjAIBaseProcessSpell, Spellbook*, SpellCastInfo*>::GetInstance()->Trigger(spellBook, spellCastInfo);
//#ifdef _DEBUG
//	std::cout << *spellCastInfo->GetMissileName() << std::endl;
//#endif // _DEBUG

	OnProcessSpell_Hook.CallOriginal(spellBook, spellCastInfo);
}

void Obj_AI_Base::ApplyHooks()
{
	IssueOrder_Hook.Apply(Patchables::pIssueOrder, OnIssueOrder);
	OnProcessSpell_Hook.Apply(Patchables::pOnProcessSpell, OnProcessSpell);
}

AIManager_Client * Obj_AI_Base::GetAIManager_Client()
{
	AIManager_Client** aiManager = reinterpret_cast<AIManager_Client**>(this + static_cast<int>(Offsets::Obj_AI_Base::AIManager));
	if (!aiManager)
		return nullptr;
	return *aiManager;
}

Spellbook * Obj_AI_Base::GetSpellbook()
{
	Spellbook** spellbook = reinterpret_cast<Spellbook**>(this + static_cast<int>(Offsets::Obj_AI_Base::SpellBook));
	if (!spellbook)
		return nullptr;
	return *spellbook;
}

std::string Obj_AI_Base::GetAIName()
{
	if (this == nullptr)
		return "Unknown";

	return reinterpret_cast<char*>(this + static_cast<int>(Offsets::Obj_AI_Base::AIName));
}

using _fnIssueOrder = void(__thiscall*)(GameObject* Player, GameObjectOrder dwOrder, Vector3* TargetPos,
	GameObject* TargetPtr, DWORD attackLoc, DWORD isPassive, uint NetWorkId);

bool Obj_AI_Base::IssueOrder(Vector3 position, GameObjectOrder order, GameObject* unit)
{
	Vector3* pPosition = new Vector3(position.x, position.y, position.z);
	_fnIssueOrder originalIssueOrder = (_fnIssueOrder)Patchables::pIssueOrder;

	if (pPosition == nullptr || this == nullptr)
	{
		return false;
	}

	// Return False if trying to attack target
	// and unit is nullptr
	if (order == GameObjectOrder::AttackUnit
		&& unit == nullptr)
	{
		return false;
	}

	DWORD issueOrderFlags1 = 0x0000000;
	DWORD issueOrderFlags2 = 0x0000000;

	switch (order)
	{
	case GameObjectOrder::HoldPosition:
		//originalIssueOrder(GameObjectOrder::Stop, position, nullptr, 0, 0, 0x0000001);
		originalIssueOrder(this, GameObjectOrder::Stop, pPosition, nullptr, 0, 0, 0x0000001);

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

	originalIssueOrder(this, order, pPosition, unit, issueOrderFlags1, issueOrderFlags2, unit ? *unit->GetNetworkId() : 0);

	return true;
}

float Obj_AI_Base::GetAttackDelay()
{
	__try
	{
		float returnValue = 0.0f;

		typedef float(__cdecl* fnGetAttackDelay)(GameObject* pObj, int index);
		fnGetAttackDelay pGetAttackDelay = reinterpret_cast<fnGetAttackDelay>(Patchables::LolBase + fnAttackDelay);

		returnValue = pGetAttackDelay(this, 64);
		//float AASpellModule = this->GetUnitStats()->mAttackSpeedMod;
		return returnValue /*/ AASpellModule*/;
	}
	__except (1) { return 0; }
}

float Obj_AI_Base::GetAttackCastDelay()
{
	__try
	{
		float returnValue = 0.0f;

		typedef float(__cdecl* fnGetAttackCastDelay)(GameObject* pObj, int index);
		fnGetAttackCastDelay pGetAttackCastDelay = reinterpret_cast<fnGetAttackCastDelay>(Patchables::LolBase + fnAttackCastDelay);

		returnValue = pGetAttackCastDelay(this, 64);

		return returnValue;
	}
	__except (1) { return 0; }
}



