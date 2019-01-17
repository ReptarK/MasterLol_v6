#pragma once
#include "AttackableUnit.h"
#include "SpellData.h"

class Spellbook;

class Navigation
{
public:
	char pad_0x0000[0x10]; //0x0000
	Vector3 vGoingTo; //0x0010 
	char pad_0x001C[0x2AC]; //0x001C
	Vector3 vVelocity; //0x02C8 
	char pad_0x02D4[0x88]; //0x02D4
	Vector3 vDashEndPos; //0x035C 
	char pad_0x0368[0x2C]; //0x0368
	__int32 isDashing; //0x0394 
	char pad_0x0398[0x26C]; //0x0398
}; //Size=0x0604

class AIManager
{
public:
	char pad_0000[4]; //0x0000
	class Navigation* pNavigation; //0x0004
};

//void __fastcall OnProcessSpell(void* SpellBook, void* edx, SpellCastInfo* castinfo)

class Obj_AI_Base
	: public AttackableUnit
{
public:
	MAKE_GET( Gold, float, Offsets::Obj_AI_Base::Gold );

	AIManager* GetAIManager();
	Spellbook* GetSpellbook();
	std::string GetAIName();

	// Game Functions
	bool IssueOrder( Vector3 pos, GameObjectOrder = GameObjectOrder::MoveTo, GameObject* = nullptr );

	float GetAttackDelay();
	float GetAttackCastDelay();
};
