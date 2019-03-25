#pragma once
#include "stdafx.h"

#define g_Offset static DWORD

#define XOR_KEY 0x5AD76FE7

//Functions
#define fnPrintChat             0x5EA090

#define fnGetAttackDelay        0x5B7B30  
#define fnGetAttackCastDelay    0x5B7A50
#define fnGetBasicAttack		0x1B3960 // 53 8B D9 B8 ? ? ? ? 8B 93

#define fnDrawCircle            0x5A7420
#define fnGetBoundingRadius		0x1F1910 // 83 EC 08 56 8B F1 83 BE ? ? ? ? ? 74 69

#define fnWorldToScreen			0x7E55F0
#define fnWorldToMinimap		0x7E55F0 // 83 EC 08 8B 44 24 0C F3 0F 10 15
#define fnBaseDrawPosition		0x1B4D80

#define fnIsTargetable          0x21FEB0
#define fnIsAlive               0x1E2810 

#define fnIsBaron				0x215FF0
#define fnIsDragon				0x215420
#define fnIsInhib               0x227380 // id = 0x20000
#define fnIsNexus               0x227130 // id = 0x20000
#define fnIsTroy                0x227470 // id = 0x1000
#define fnIsTurret              0x227380 // id = 0x2000
#define fnIsMinion              0x2271F0 // id = 0x800
#define fnIsHero                0x2271B0 // id = 0x1000
#define fnIsMissile             0x227210 // id = 0x8000

#define fnIssueOrder            0x1BE7B0

#define fnGetSpellState         0x5A4EE0
#define fnCastSpell             0x5AF100 
#define fnUpdateChargeableSpell 0x5B1890

// CampManager
#define fnGetTimerExpiry		0x1B8750 //	NOT UPDATED
#define fnFindCamp				0x1B0790 //	NOT UPDATED

#define fnIsNotWall				0x758340

//General offsets
#define oChatClientPtr		0x1695CC0		// "Chat_Box_Open"				-> previous function -> first instruction -> mov ecx, dword_oChatClientPtr
#define oLocalPlayer		0x2F43900		// "PostGameSetup"				-> mov eax, dword_oLocalPlayer
#define oObjManager			0x2F43098		// "Reconnect being processed"	-> mov ecx, offset byte_37F6C88
#define oHudInstance		0x16984D0		// "PerSide.ini"
#define oGameTime			0x2F3F7B0		// 83 EC 10 53 8B 1D ? ? ? ? 55 -> decompile -> if ( (float)(v17 - *(float *)&dword_GameTime) < 0.0 )
#define oRenderer			0x2F60A5C		// "UI_LoadScreen_Frame_01.dds" -> five instructions above -> cmp dword_oRenderer, 0
#define oUnderMouseObj		0x22E8CEC		// C7 05 ? ? ? ? ? ? ? ? E8 ? ? ? ? 83 C4 04 FF B4 24
#define oCampManagerClient	0x16843D4		// "game_ping_[Jungle]_Alive" -> above : mov     ecx, dword_19543D4
#define oTacticalMap		0x2F438F4		// A1 ? ? ? ? 56 8B F1 85 C0 74 1A -> first instruction -> mov eax, dword_oTacticalMap || "MinimapTooltip" -> first xref -> 3 instructions down -> mov ecx, dword_oTacticalMap

#define oD3DInstance		0x2F66BBC		// 8B 11 85 D2 74 0F -> mov  ecx, dword_30B392C 
											// OR
											// "Failed to create DX9Query" -> first instruction -> mov eax, dword_30B392C




class Patchables
{
public:
	static bool Initialize();

	// Game Functions
	g_Offset LolBase;

private:
	static void InitializePointers();
};




/////////
// OLD //
/////////

//#define fnIssueOrder 0x1C9B10 // 8.12
//#define fnMainLoop 0x75B510 // 8.12
//#define fnAttackDelay 0x554E50 // 8.12
//#define fnAttackCastDelay 0x554D40 // 8.11
//#define fnCastSpell 0x54E480 // 8.12
//#define fnSpellstate 0x543934 // 8.12
//#define fnDrawCircle 0x545760 // 8.12
//#define fnOnProcessSpell 0x54F850 // 8.12
//#define fnObjectCreate 0x2E2710 // 8.12
//#define fnObjectDelete 0x2D80B0 // 8.12
//#define fnSendChat 0x645DA0
//#define fnPrintChat 0x577CED
//
//#define oRenderer 0x2E616B0 // 8.12
//#define oLocalPlayer 0x2E3B2E0 // 8.12
//#define oObjectManager 0x2E3A680 // 8.12
//#define oUnderMouseObject 0x21E3C64 // 8.12
//#define oCursor 0x1592CFC // 8.12
//#define oGameTime 0x2E3739C // 8.12
//#define oIsGameFocused 0x2E59D00 // 8.12