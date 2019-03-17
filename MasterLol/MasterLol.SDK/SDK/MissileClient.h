#pragma once
#include "GameObject.h"
#include "SpellData.h"
#include "SpellInfo.h"

class MissileClientData
{
public:
	SpellInfo * GetSpellInfo()
	{
		if (this != nullptr)
		{
			return reinterpret_cast<SpellInfo*>(this);
		}

		return nullptr;
	}
};

/*
MissileSpellInfo = 0x278,
Level = 0x2CC,
CasterIndex = 0x2D4,
LaunchPosition = 0x2EC,
EndPosition = 0x2F8,
CastPosition = 0x2F8,
TargetIndex = 0x31C,

WindupTime = 0x720,
mAttackDelay = 0x744,
IsAutoAttack = 0x748,
CreatedTime = 0x79C
*/

class MissileClient
	: public GameObject
{
public:

	SpellInfo* GetMissileSpellInfo() {
		return *reinterpret_cast<SpellInfo**>(this + static_cast<int>(Offsets::MissileClient::MissileSpellInfo));
	}

	ESpellSlot::ESpellSlot GetSlot() {
		int slot = *reinterpret_cast<int*>(this + static_cast<int>(Offsets::MissileClient::Slot));
		if (slot < 0)
			return ESpellSlot::AA;
		else
			return static_cast<ESpellSlot::ESpellSlot>(slot);
	}

	uint GetSpellLevel(){
		return *reinterpret_cast<uint*>(this + static_cast<int>(Offsets::MissileClient::Level));
	}

	uint GetCasterIndex(){
		return *reinterpret_cast<uint*>(this + static_cast<int>(Offsets::MissileClient::CasterIndex));
	}

	uint GetTargetIndex(){
		return *reinterpret_cast<uint*>(this + static_cast<int>(Offsets::MissileClient::TargetIndex));
	}

	Vector3 GetLaunchPosition() {
		return *reinterpret_cast<Vector3*>(this + static_cast<int>(Offsets::MissileClient::LaunchPosition));
	}

	Vector3 GetEndPosition() {
		return *reinterpret_cast<Vector3*>(this + static_cast<int>(Offsets::MissileClient::EndPosition));
	}

	Vector3 GetCastPosition() {
		return *reinterpret_cast<Vector3*>(this + static_cast<int>(Offsets::MissileClient::CastPosition));
	}

	float GetWindupTime() {
		return *reinterpret_cast<float*>(this + static_cast<int>(Offsets::MissileClient::WindupTime));
	}

	float GetAttackDelay() {
		return *reinterpret_cast<float*>(this + static_cast<int>(Offsets::MissileClient::AttackDelay));
	}

	int GetCreatedTimeMs(){
		return (int)(1000 * (*reinterpret_cast<float*>(this + static_cast<int>(Offsets::MissileClient::CreatedTime))));
	}
};
