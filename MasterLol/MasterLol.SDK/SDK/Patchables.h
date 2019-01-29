#pragma once
#include "stdafx.h"

#define g_Offset static DWORD

#define XOR_KEY 0xEFEE81C4

//Functions
#define fnPrintChat             0x5C9570
#define fnGetAttackDelay        0x597D10
#define fnGetAttackCastDelay    0x589AC0
#define fnDrawCircle            0x587920

#define fnIsAlive               0x1DFA40
#define fnIsTargetable          0x221CE0

#define fnIsDragon				0x215090
#define fnIsBaron				0x215CE0
#define fnIsInhib               0x227830 //id = 0x20000
#define fnIsNexus               0x227930 //id = 0x20000
#define fnIsTroy                0x227C70 //id = 0x1000
#define fnIsTurret              0x227B80 //id = 0x2000
#define fnIsMinion              0x2279F0 //id = 0x800
#define fnIsHero                0x2279B0 //id = 0x1000
#define fnIsMissile             0x227A10 //id = 0x8000

#define fnIssueOrder            0x1BCEE0
#define fnGetSpellState         0x5760D0
#define fnCastSpell             0x590D20
#define fnUpdateChargeableSpell 0x583AC0

//General offsets
#define oChatClientPtr 0x15EE7B0		// "Chat_Box_Open"				-> previous function -> first instruction -> mov ecx, dword_oChatClientPtr
#define oLocalPlayer   0x2E996BC		// "PostGameSetup"				-> mov eax, dword_oLocalPlayer
#define oObjManager    0x2E99120		// "Reconnect being processed"	-> mov ecx, offset byte_37F6C88
#define oGameTime      0x2E957C8		// 83 EC 10 53 8B 1D ? ? ? ? 55 -> decompile -> if ( (float)(v17 - *(float *)&dword_GameTime) < 0.0 )
#define oHudInstance   0x15F0E48		// "PerSide.ini"
#define oRenderer      0x2EB51D4		// "UI_LoadScreen_Frame_01.dds" -> cmp dword_oRenderer, 0
#define oUnderMouseObj 0x2241DBC		// C7 05 ? ? ? ? ? ? ? ? E8 ? ? ? ? 83 C4 04 FF B4 24



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