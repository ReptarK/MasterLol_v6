#pragma once

class Offsets
{
public:
	////////////////////--HudInstance--/////////////////////////

	enum class HudInstance
	{
		GameCursor = 0x14
	};

	enum class GameCursor
	{
		UnderMouseObjPosition = 0x10,
		Position              = 0x1C
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
		//IsInvulnerable	= 0x0394,
		//IsTargetable	= 0x060C,

		Mana		    = 0x44C,
		MaxMana		    = Mana + 0x10,
		Health		    = 0xF7C,
		MaxHealth	    = Health + 0x10,

		AllShield		= 0x6B8,
		PhisicalShield	= AllShield + 0x10,
		MagicalShield	= PhisicalShield + 0x10,
		StopShieldFade	= MagicalShield + 0x20,

		CaracterState	= 0x804,
		UnitStats		= 0x1818,
		CombatType		= 0x1DC8,
	};

	enum class Obj_AI_Base
	{
		Gold		= 0x1C88,
		AIName		= 0x2460,

		SpellBook	= 0x29F0,
	};

	enum class AIHeroClient
	{
		Level = 0x4B2C
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
		ManaCostQ = 0x28,
		ManaCostW = ManaCostQ + 0x10,
		ManaCostE = ManaCostQ + ( 0x10 * 2 ),
		ManaCostR = ManaCostQ + ( 0x10 * 3 ),

		GetSpells = 0x530
	};

	enum class SpellDataInst
	{
		Level             = 0x20,
		CooldownExpires   = 0x28,
		Ammo              = 0x2C,
		AmmoRechargeStart = 0x5C,
		ToggleState       = 0x68, // Karthus
		Cooldown          = 0x6C,
		SpellInfo         = 0x124
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
		Coefficient			= 0x200,
		Coefficient2		= 0x204,
		CooldownTime		= 0x280,
		CastRange			= 0x3B4,
		CastRadius			= 0x3EC,
		CastConeAngle		= 0x41C,
		CastConeDistance	= 0x420,
		CastTargetAdditionalUnitsRadius		= 0x424,
		LuaOnMissileUpdateDistanceInterval	= 0x428,
		SpellDamageRatio	= 0x440,
		PhysicalDamageRatio = 0x444,
		MissileSpeed		= 0x450,
		LineWidth			= 0x484,
		ManaCost			= 0x520,
		CastType			= 0x664
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
