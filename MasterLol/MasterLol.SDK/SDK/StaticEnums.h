#pragma once
#include"EnumMacro.h"

enum class ENETCHANNEL
{
	Handshake = 0,
	C2S,
	GamePlay,
	S2C,
	LowPriority,
	Communication,
	LoadingScreen
};

enum class ESENDPROTOCOL
{
	Reliable = 0,
	NoFlags,
	Unsequenced
};

enum class EGameObjectOrder
{
	HoldPosition = 1,
	MoveTo,
	AttackUnit,
	AutoAttackPet,
	AutoAttack,
	MovePet,
	AttackTo,
	Stop = 10
};

enum class EGameObjectTeam
{
	Unknown = 0,
	Order = 100,
	Chaos = 200,
	Neutral = 300
};

enum class EGameState
{
	Connecting = 1,
	Running = 2,
	Paused = 3,
	Finished = 4,
	Exiting = 5
};

#pragma region SPELLS

DECLARE_ENUM(ESummonerSpell,
	SummonerHeal,
	SummonerGhost,
	SummonerBarrier,
	SummonerExhaust,
	SummonerMark,
	SummonerClarity,
	SummonerFlash,
	SummonerTeleport,
	SummonerSmite,
	S5_SummonerSmiteDuel,
	S5_SummonerSmitePlayerGanker,
	SummonerCleanse,
	SummonerIgnite
)

DECLARE_ENUM( ESpellCastType,
	Unknown,
	Targeted,
	Circle,
	MissileLine,
	Self,
	MissileAoe,
	Line,
	Cone,
	Arc,
	Free
)

DECLARE_ENUM( ESpellSlot,

	Q,
	W,
	E,
	R,
	Summoner1,
	Summoner2,
	Item1,
	Item2,
	Item3,
	Item4,
	Item5,
	Item6,
	Trinket,
	Recall,
	AA,
	Unknown
)

enum class ESpellState
{
	//Possible flags

	Ready = 0,
	NotAvailable = 4,
	Surpressed = 8,
	NotLearned = 12,
	Cooldown = 32,
	NoMana = 64,
	Unknown
};

enum class EToggleState
{
	Unknown = 0,
	NotActive,
	Active
};

DECLARE_ENUM( ESpellStage,
	Default,
	SecondCast,
	Empowered,
	EmpoweredSecondCast,
	DamagePerSecond,
	Detonation,
	Passive,
	WayBack,
	SecondForm
)

DECLARE_ENUM( ESpellDamageType,
	Physical,
	Magical,
	True
)

DECLARE_ENUM( ESpellScalingTarget,
	Source,
	Target
)

DECLARE_ENUM( ESpellScalingType,
	AbilityPoints,
	AttackPoints,
	BonusAttackPoints,
	MaxHealth,
	MaxMana
)
#pragma endregion

enum class EGameMode
{
	Connecting = 1,
	Running = 2,
	Paused = 3,
	Finished = 4,
	Exiting = 5
};

enum class EGameMap
{
	CrystalScar = 8,
	TwistedTreeline = 10,
	SummonersRift = 11,
	HowlingAbyss = 12
};

enum class ECollisionFlags
{
	None = 0,
	Grass = 1,
	Wall = 2,
	Building = 64,
	Prop = 128,
	GlobalVision = 256
};

enum class EUnitType
{
	Unknown   = 0,
	Minion    = 0x800,
	Troy      = 0x801,
	Dragon    = 0x802,
	Baron     = 0x803,
	Hero      = 0x1000,
	Turret    = 0x2000,
	Missile   = 0x8000,
	Inhibitor = 0x20000,
	Nexus     = 0x20001,
};

enum class EUnitId
{
	Unknown   = 0,
	Minion    = 0x800,
	Troy      = 0x801,
	Dragon    = 0x802,
	Baron     = 0x803,
	Hero      = 0x1000,
	Turret    = 0x2000,
	Missile   = 0x8000,
	Inhibitor = 0x20000,
	Nexus     = 0x20001,
};

/*
enum class UnitType
{
	NeutralMinionCamp = 0,
	FollowerObject = 1,
	FollowerObjectWithLerpMovement = 2,
	AIHeroClient = 3,
	AIMarker = 4,
	AIMinionClient = 5,
	LevelPropAIClient = 6,
	AITurretClient = 7,
	AITurretCommon = 8,
	obj_GeneralParticleEmitter = 9,
	GameObject = 10,
	MissileClient = 11,
	DrawFX = 12,
	UnrevealedTarget = 13,
	BarracksDampener = 14,
	Barracks = 15,
	AnimatedBuilding = 16,
	BuildingClient = 17,
	obj_Lake = 18,
	obj_Levelsizer = 19,
	obj_NavPoint = 20,
	obj_SpawnPoint = 21,
	obj_LampBulb = 22,
	GrassObject = 23,
	HQ = 24,
	obj_InfoPoint = 25,
	LevelPropGameObject = 26,
	LevelPropSpawnerPoint = 27,
	Shop = 28,
	obj_Turret = 29,
	Unknown
};*/

enum class BuffType {
	Internal = 0,
	Aura = 1,
	CombatEnchancer = 2,
	CombatDehancer = 3,
	SpellShield = 4,
	Stun = 5,
	Invisibility = 6,
	Silence = 7,
	Taunt = 8,
	Polymorph = 9,
	Slow = 10,
	Snare = 11,
	Damage = 12,
	Heal = 13,
	Haste = 14,
	SpellImmunity = 15,
	PhysicalImmunity = 16,
	Invulnerability = 17,
	Sleep = 18,
	NearSight = 19,
	Frenzy = 20,
	Fear = 21,
	Charm = 22,
	Poison = 23,
	Suppression = 24,
	Blind = 25,
	Counter = 26,
	Shred = 27,
	Flee = 28,
	Knockup = 29,
	Knockback = 30,
	Disarm = 31
};

DECLARE_ENUM(EPriority,
	Unknown,
	Lowest,
	Low,
	Medium,
	High,
	Highest
)

DECLARE_ENUM(EChampion,

	Aatrox,
	Ahri,
	Akali,
	Alistar,
	Amumu,
	Anivia,
	Annie,
	Ashe,
	Azir,
	Bard,
	Blitzcrank,
	Brand,
	Braum,
	Caitlyn,
	Cassiopeia,
	Chogath,
	Corki,
	Darius,
	Diana,
	DrMundo,
	Draven,
	Ekko,
	Elise,
	Evelynn,
	Ezreal,
	FiddleSticks,
	Fiora,
	Fizz,
	Galio,
	Gangplank,
	Garen,
	Gnar,
	Gragas,
	Graves,
	Hecarim,
	Heimerdinger,
	Illaoi,
	Irelia,
	Janna,
	JarvanIV,
	Jax,
	Jayce,
	Jhin,
	Jinx,
	Kalista,
	Karma,
	Karthus,
	Kassadin,
	Katarina,
	Kayle,
	Kayn,
	Kennen,
	Khazix,
	Kindred,
	Kled,
	KogMaw,
	Leblanc,
	LeeSin,
	Leona,
	Lissandra,
	Lucian,
	Lulu,
	Lux,
	Malphite,
	Malzahar,
	Maokai,
	MasterYi,
	MissFortune,
	Mordekaiser,
	Morgana,
	Nami,
	Nasus,
	Nautilus,
	Nidalee,
	Nocturne,
	Nunu,
	Olaf,
	Orianna,
	Pantheon,
	Poppy,
	Pyke,
	Quinn,
	Rammus,
	RekSai,
	Renekton,
	Rengar,
	Riven,
	Rumble,
	Ryze,
	Sejuani,
	Shaco,
	Shen,
	Shyvana,
	Singed,
	Sion,
	Sivir,
	Skarner,
	Sona,
	Soraka,
	Swain,
	Syndra,
	TahmKench,
	Talon,
	Taric,
	Teemo,
	Thresh,
	Tristana,
	Trundle,
	Tryndamere,
	TwistedFate,
	Twitch,
	Udyr,
	Urgot,
	Varus,
	Vayne,
	Veigar,
	Velkoz,
	Vi,
	Viktor,
	Vladimir,
	Volibear,
	Warwick,
	MonkeyKing,
	Xerath,
	XinZhao,
	Yasuo,
	Yorick,
	Zac,
	Zed,
	Ziggs,
	Zilean,
	Zyra,
	//New Champs
	KaiSa,
	Zoe,
	Ornn,
	Rakan,
	Xayah,
	Camille,
	Ivern,
	Taliyah,
	AurelionSol,
	Unknown
)
