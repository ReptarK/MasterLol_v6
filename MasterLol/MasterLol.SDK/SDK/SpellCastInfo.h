#pragma once
#include "stdafx.h"
#include "SpellInfo.h"
#include "MissileClient.h"
#include "ObjectManager.h"

class SpellCastInfo
{
public:
	char pad_0000[8]; //0x0000
	class SpellInfo* mSpellInfo; //0x0008
	int32_t mSlot; //0x000C
	char pad_0010[4]; //0x0010
	uint16_t mMissileIndex; //0x0014
	char pad_0016[10]; //0x0016
	LolString mCasterName; //0x0020
	char pad_0038[36]; //0x0038
	int32_t mSpellLevel; //0x005C
	char pad_0060[28]; //0x0060
	Vector3 mStartPosition; //0x007C
	Vector3 mEndPosition; //0x0088
	Vector3 mUnkVector; //0x0094
	Vector3 mDirection; //0x00A0
	bool mIsAutoAttack; //0x00AC
	char pad_00AD[1027]; //0x00AD
	float mWindupTime; //0x04B0
	char pad_04B4[16]; //0x04B4
	float mCooldown; //0x04C4
	char pad_04C8[92]; //0x04C8
	float mCastTime; //0x0524
	char pad_0528[4]; //0x0528
	float mEndTime; //0x052C
	char pad_0530[76]; //0x0530
	Vector3 mRelativeEndPosition; //0x057C

	inline SpellInfo* GetSpellInfo() {
		return *reinterpret_cast<SpellInfo**>(this + static_cast<__int32>(Offsets::SpellCastInfo::SpellInfo));
	}

	inline MissileClient* GetMissileClient(){
		return (MissileClient*)ObjectManager::GetUnitArray()[this->mMissileIndex];
	}

	inline int GetUniqueId() {
		return 1000 * ((int)this->mEndTime + (int)this->mCastTime);
	}
};