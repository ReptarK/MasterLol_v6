#pragma once

class Offsets
{
public:
	////////////////////--CURSOR--/////////////////////////

	enum class GameCursor
	{
		Position = 0x9C
	};

	////////////////////--GAMEOBJECTS--/////////////////////////

	enum class GameObject
	{
		Index			=	0x20,
		Team			=	0x4C,
		Name			=	0x88,
		NetworkId		=	0x110,
		Position		=	0x260,
		VisibleOnScreen =	0x420
	};

	enum class AttackableUnit
	{
		// Booleans
		IsInvulnerable	= 0x0394,
		IsTargetable	= 0x060C,

		Mana		= 0x2CC,
		MaxMana		= Mana + 0x10,
		Health		= 0xF7C,
		MaxHealth	= Health + 0x10,

		AllShield		= 0x6B8,
		PhisicalShield	= AllShield + 0x10,
		MagicalShield	= PhisicalShield + 0x10,
		StopShieldFade	= MagicalShield + 0x20,

		CaracterState	= 0x804,
		UnitStats		= 0xE20,
		CombatType		= 0x16E4,
	};

	enum class Obj_AI_Base
	{
		Gold = 0x1268,

		AIName		= 0x179C,
		AIManager	= 0x17B4,

		ManaCost_Q	= 0x1D00,
		ManaCost_W	= ManaCost_Q + (0x16 * 1),
		ManaCost_E	= ManaCost_Q + (0x16 * 2),
		ManaCost_R	= ManaCost_Q + (0x16 * 3),
		SpellBook	= 0x2174,
	};

	enum class AIHeroClient
	{
		Level = 0x3934
	};

	enum class MissileClient
	{
		LaunchPos			= 0x13C,
		DestPos				= 0x148,
		MissileSpellInfo	= 0x104,
		CasterId			= 0x124,
		TargetId			= 0x16C
	};

	////////////////////--SPELLBOOK--/////////////////////////

	enum class Spellbook
	{
		GetSpells = 0x530
	};

	enum class SpellDataInst
	{
		Level = 0x1C,
		CooldownExpires = 0x24,
		Ammo = 0x28,
		AmmoRechargeStart = 0x58,
		ToggleState = 0x64, // Karthus
		Cooldown = 0x68,
		SpellInfo = 0x11C
	};

	enum class SpellInfo
	{
		GetSpellData = 0x38,
	};

	enum class SpellData
	{
		MissileName			= 0x58,
		SpellName			= 0x7C,
		EffectAmount		= 0xD0,
		Coefficient			= 0x1F4,
		Coefficient2		= 0x1F8,
		CooldownTime		= 0x274,
		CastRange			= 0x390,
		CastRadius			= 0x03DC,
		CastConeAngle		= 0x400,
		CastConeDistance	= 0x404,
		CastTargetAdditionalUnitsRadius		= 0x0408,
		LuaOnMissileUpdateDistanceInterval	= 0x040C,
		CastType			= 0x0414,
		SpellDamageRatio	= 0x041C,
		PhysicalDamageRatio = 0x420,
		MissileSpeed		= 0x042C,
		LineWidth			= 0x460,
		ManaCost			= 0x4FC,
		TargetingType		= 0x600
	};

	enum class SpellCastInfo
	{
		SpellInfo			= 0x0,
		CasterIndex			= 0x20,
		SourcePosition		= 0x38,
		DestinationPosition = 0x44,
		IsAutoAttack		= 0x68,
		TargetIndex			= 0x6C,
		MissileClient		= 0x1FC,
		WindupTime			= 0x46C,
		AttackDelay			= 0x47C,
		Slot				= 0x494
	};
};
