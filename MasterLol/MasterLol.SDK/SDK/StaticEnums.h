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

enum class GameObjectOrder
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

enum class GameObjectTeam
{
	Unknown = 0,
	Order = 100,
	Chaos = 200,
	Neutral = 300
};

enum class GameState
{
	Connecting = 1,
	Running = 2,
	Paused = 3,
	Finished = 4,
	Exiting = 5
};

#pragma region SPELLS

DECLARE_ENUM(SummonerSpellEnum,
	SummonerHeal,
	SummonerGhost,
	SummonerBarrier,
	SummonerExhaust,
	SummonerMark,
	SummonerClarity,
	SummonerFlash,
	SummonerTeleport,
	SummonerSmite,
	SummonerCleanse,
	SummonerIgnite
)

DECLARE_ENUM( SpellCastType,
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
	Unknown
)

enum class SpellState
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

enum class ToggleState
{
	Unknown = 0,
	NotActive,
	Active
};

DECLARE_ENUM( SpellStage,
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

DECLARE_ENUM( SpellDamageType,
	Physical,
	Magical,
	True
)

DECLARE_ENUM( SpellScalingTarget,
	Source,
	Target
)

DECLARE_ENUM( SpellScalingType,
	AbilityPoints,
	AttackPoints,
	BonusAttackPoints,
	MaxHealth,
	MaxMana
)
#pragma endregion

enum class GameMode
{
	Connecting = 1,
	Running = 2,
	Paused = 3,
	Finished = 4,
	Exiting = 5
};

enum class GameMap
{
	CrystalScar = 8,
	TwistedTreeline = 10,
	SummonersRift = 11,
	HowlingAbyss = 12
};

enum class CollisionFlags
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
	Hero,
	Minion,
	Turret,
	Inhibitor,
	Nexus,
	Troy,
	Missile,
	Unknown
};

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
};

DECLARE_ENUM(Priority,
	Unknown,
	Lowest,
	Low,
	Medium,
	High,
	Highest
)

DECLARE_ENUM(Champion,

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
