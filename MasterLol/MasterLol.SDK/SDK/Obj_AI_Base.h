#pragma once
#include "AttackableUnit.h"
#include "SpellData.h"

class Spellbook;

class Navigation
{
public:
	char pad_0004[12]; //0x0004
	Vector3 GoingTo; //0x0010
	char pad_001C[380]; //0x001C
	int32_t IsMoving; //0x0198
	char pad_019C[284]; //0x019C
	bool unkByte; //0x02B8
	char pad_02B9[15]; //0x02B9
	Vector3 Velocity; //0x02C8
	char pad_02D4[136]; //0x02D4
	Vector3 DashEndPosition; //0x035C
	char pad_0368[44]; //0x0368
	bool IsDashing; //0x0394
	char pad_0395[15]; //0x0395
	uint32_t flag_100_200; //0x03A4

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual bool IsStanding();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual DWORD* unkPtr();
	virtual void Function13();
	virtual void Function14();
	virtual int signed_intFunc();
	virtual void Function16();
	virtual void Function17();
	virtual float GetMovementSpeed();
	virtual float GetFloat();
	virtual void Function20();
	virtual void Function21();
	virtual void Function22();
	virtual void Function23();
	virtual void Function24();
	virtual void Function25();
	virtual void Function26();
	virtual void* fn27_voidPtr(bool a1);
	virtual void Function28();
	virtual void Function29();
}; //Size: 0x0848

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
