#pragma once
#include "GameObject.h"

//namespace Enums
//{
#pragma region ENUMS
#pragma region UNIT STATS
class UnitStats
{
public:
	float mPercentCooldownMod; //0x0000
	char pad_0004[12]; //0x0004
	float mPercentCooldownCapMod; //0x0010
	char pad_0014[12]; //0x0014
	float mPassiveCooldownEndTime; //0x0020
	char pad_0024[12]; //0x0024
	float mPassiveCooldownTotalTime; //0x0030
	char pad_0034[60]; //0x0034
	float mFlatPhysicalDamageMod; //0x0070
	char pad_0074[12]; //0x0074
	float mPercentPhysicalDamageMod; //0x0080
	char pad_0084[12]; //0x0084
	float mPercentBonusPhysicalDamageMod; //0x0090
	char pad_0094[12]; //0x0094
	float mPercentBasePhysicalDamageAsFlatBonusMod; //0x00A0
	char pad_00A4[12]; //0x00A4
	float mFlatMagicDamageMod; //0x00B0
	char pad_00B4[12]; //0x00B4
	float mPercentMagicDamageMod; //0x00C0
	char pad_00C4[12]; //0x00C4
	float mFlatMagicReduction; //0x00D0
	char pad_00D4[12]; //0x00D4
	float mPercentMagicReduction; //0x00E0
	char pad_00E4[12]; //0x00E4
	float mFlatCastRangeMod; //0x00F0
	char pad_00F4[12]; //0x00F4
	float mAttackSpeedMod; //0x0100
	char pad_0104[12]; //0x0104
	float mFlatBaseAttackDamageMod; //0x0110
	char pad_0114[12]; //0x0114
	float mBaseAttackDamageSansPercentScale; //0x0120
	char pad_0124[12]; //0x0124
	float mBaseAttackDamage; //0x0130
	char pad_0134[12]; //0x0134
	float mPercentBaseAttackDamageMod; //0x0140
	char pad_0144[12]; //0x0144
	float mBaseAbilityDamage; //0x0150
	char pad_0154[44]; //0x0154
	float mScaleSkinCoef; //0x0180
	char pad_0184[12]; //0x0184
	float mDodge; //0x0190
	char pad_0194[12]; //0x0194
	float mCrit; //0x01A0
	char pad_01A4[12]; //0x01A4
	float mArmor; //0x01B0
	char pad_01B4[12]; //0x01B4
	float mBonusArmor; //0x01C0
	char pad_01C4[12]; //0x01C4
	float mMagicResist; //0x01D0
	char pad_01D4[12]; //0x01D4
	float mBonusMagicResist; //0x01E0
	char pad_01E4[12]; //0x01E4
	float mHPRegenRate; //0x01F0
	char pad_01F4[12]; //0x01F4
	float mBaseHPRegenRate; //0x0200
	char pad_0204[12]; //0x0204
	float mMoveSpeed; //0x0210
	char pad_0214[28]; //0x0214
	float mAttackRange; //0x0230
	char pad_0234[44]; //0x0234
	float mFlatArmorPenetration; //0x0260
	char pad_0264[12]; //0x0264
	float mPhysicalLethality; //0x0270
	char pad_0274[12]; //0x0274
	float mPercentBonusArmorPenetration; //0x0280
	char pad_0284[28]; //0x0284
	float mPercentCritBonusArmorPenetration; //0x02A0
	char pad_02A4[12]; //0x02A4
	float mPercentCritTotalArmorPenetration; //0x02B0
	char pad_02B4[12]; //0x02B4
	float mFlatMagicPenetration; //0x02C0
	char pad_02C4[12]; //0x02C4
	float mMagicLethality; //0x02D0
	char pad_02D4[44]; //0x02D4
	float mPercentLifeStealMod; //0x0300
	float mPercentSpellVampMod; //0x0304
	char pad_0308[40]; //0x0308
	float mPercentCCReduction; //0x0330
}; //Size: 0x0334
#pragma endregion

	enum class CombatType
	{
		Melee = 1,
		Ranged = 2
	};

	enum class CaracterState
	{
		CanMove = 3,
		CanAttack = 2,	//0b 0010 0000 0000 0000 0000 0000 1111 || 0x0200000F
		isTaunt = 7,	//0b 0010 0000 0000 0000 0000 1000 1111 || 0x0200008F
		//Root,			//0b 0010 0000 0000 0000 0000 0000 0111 || 0x02000007 = 
		isSlow = 24,	//0b ‭0011 0000 0000 0000 0000 0000 1111‬ || 0x0300000F = 24
		//Stun,			//0b 0010 0000 0000 0000 0000 1000 0010 || 0x02000002 = 7
		//Dash			//0b ‭0010 0000 0000 0000 0000 0000 0010‬ || 0x02000002
		isSpeeding = 13	//0b ‭0010 0000 0000 0010 0000 0000 1111 || 0x0200200F‬ = 13
	};

#pragma endregion
//}

class AttackableUnit
	: public GameObject
{
public:
	MAKE_GET(IsInvulnerable, bool, Offsets::AttackableUnit::IsInvulnerable);
	MAKE_GET(IsTargetable, bool, Offsets::AttackableUnit::IsTargetable);

	MAKE_GET(Health, float, Offsets::AttackableUnit::Health);
	MAKE_GET(MaxHealth, float, Offsets::AttackableUnit::MaxHealth);
	MAKE_GET(Mana, float, Offsets::AttackableUnit::Mana);
	MAKE_GET(MaxMana, float, Offsets::AttackableUnit::MaxMana);

	MAKE_GET(AllShield, float, Offsets::AttackableUnit::AllShield);
	MAKE_GET(MagicalShield, float, Offsets::AttackableUnit::MagicalShield);
	MAKE_GET(PhisicalShield, float, Offsets::AttackableUnit::PhisicalShield);
	MAKE_GET(StopShieldFade, float, Offsets::AttackableUnit::StopShieldFade);

	MAKE_GET(CaracterState, __int32, Offsets::AttackableUnit::CaracterState);

	MAKE_GET(UnitStats, UnitStats, Offsets::AttackableUnit::UnitStats);
	MAKE_GET(CombatType, CombatType, Offsets::AttackableUnit::CombatType);


	// Methods
	bool IsCaracterState(CaracterState);
	bool IsStunned();

	bool IsMelee();
	bool IsRanged();

	float GetHealthPercent();
	float GetManaPercent();
};


