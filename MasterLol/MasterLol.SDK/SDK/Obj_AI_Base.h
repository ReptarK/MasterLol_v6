#pragma once
#include "AttackableUnit.h"
#include "SpellData.h"
#include "Navigation.h"

class Spellbook;

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

	static void ApplyHooks();

	Navigation* GetNavigation();
	Spellbook* GetSpellbook();
	std::string GetAIName();

	// Game Functions
	bool IssueOrder( Vector3 pos, EGameObjectOrder = EGameObjectOrder::MoveTo, GameObject* = nullptr );

	float GetAttackDelay();
	float GetAttackCastDelay();
};
