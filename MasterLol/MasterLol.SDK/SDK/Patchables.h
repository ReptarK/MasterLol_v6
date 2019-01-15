#pragma once
#include "stdafx.h"

#define g_Offset static DWORD

//Functions
#define fnPrintChat 0x5B2710
#define fnGetAttackDelay 0x589BA0
#define fnGetAttackCastDelay 0x589AC0
#define fnDrawCircle 0x578960
#define fnIsAlive 0x1DF120
#define fnIsInhib 0x226A10
#define fnIsNexus 0x226B10
#define fnIsTroy 0x226E50
#define fnIsTurret 0x226D60
#define fnIsMinion 0x226BD0
#define fnIsHero 0x226B90
#define fnIsMissile 0x226BF0
#define fnIsTargetable 0x220EB0
#define fnIssueOrder 0x1BCA40
#define fnGetSpellState 0x5760D0
#define fnCastSpell 0x581020
#define fnUpdateChargeableSpell 0x583AC0

//General offsets
#define oChatClientPtr 0x15CC330	// "Chat_Box_Open"				-> previous function -> first instruction -> mov ecx, dword_oChatClientPtr
#define oLocalPlayer 0x2E774E8		// "PostGameSetup"				-> mov eax, dword_oLocalPlayer
#define oObjManager 0x2E76C88		// "Reconnect being processed"	-> mov ecx, offset byte_37F6C88
#define oGameTime 0x2E73400
#define oHudInstance 0x15CE9CC		// "PerSide.ini"
#define oGameVersion 0x2E80678
#define oRenderer 0x2E92DD4			// "UI_LoadScreen_Frame_01.dds" -> cmp dword_oRenderer, 0
#define oZoomClass 0x2E73358



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