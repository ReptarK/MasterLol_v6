#include "stdafx.h"
#include "Game.h"

#include "Draw.h"
#include "ObjectManager.h"
#include "Spellbook.h"
#include "Obj_AI_Base.h"
#include "EventManager.h"

#pragma region Event Linking
template <EventIndex uniqueEventNumber, typename T, typename ... TArgs>
EventHandler<uniqueEventNumber, T, TArgs...>* EventHandler<uniqueEventNumber, T, TArgs...>::instance = nullptr;

static void linkEvents()
{
	//Game
	EventHandler<EventIndex::OnUpdate, EventDefines::OnMainLoop>::GetInstance()->Add( nullptr );
	EventHandler<EventIndex::OnUpdate, EventDefines::OnMainLoop>::GetInstance()->Remove( nullptr );
	EventHandler<EventIndex::OnCreateMissile, EventDefines::OnCreateMissile, MissileClient*, Obj_AI_Base*>::GetInstance()->Add(nullptr);
	EventHandler<EventIndex::OnCreateMissile, EventDefines::OnCreateMissile, MissileClient*, Obj_AI_Base*>::GetInstance()->Remove(nullptr);
	EventHandler<EventIndex::OnProcessSpell, EventDefines::OnProcessSpell, SpellCastInfo*, Obj_AI_Base*>::GetInstance()->Add(nullptr);
	EventHandler<EventIndex::OnProcessSpell, EventDefines::OnProcessSpell, SpellCastInfo*, Obj_AI_Base*>::GetInstance()->Remove(nullptr);
	//Drawing
	EventHandler<EventIndex::OnDrawingEndScene, EventDefines::OnDrawingEndScene, IDirect3DDevice9*>::GetInstance()->Add( nullptr );
	EventHandler<EventIndex::OnDrawingEndScene, EventDefines::OnDrawingEndScene, IDirect3DDevice9*>::GetInstance()->Remove( nullptr );
	EventHandler<EventIndex::OnReset, EventDefines::OnReset, IDirect3DDevice9*, D3DPRESENT_PARAMETERS*>::GetInstance()->Add( nullptr );
	EventHandler<EventIndex::OnReset, EventDefines::OnReset, IDirect3DDevice9*, D3DPRESENT_PARAMETERS*>::GetInstance()->Remove( nullptr );
	EventHandler<EventIndex::OnDrawingPresent, EventDefines::OnDrawingPresent, LPDIRECT3DDEVICE9, const RECT*, const RECT*, HWND, const RGNDATA*>::GetInstance()->Add( nullptr );
	EventHandler<EventIndex::OnDrawingPresent, EventDefines::OnDrawingPresent, LPDIRECT3DDEVICE9, const RECT*, const RECT*, HWND, const RGNDATA*>::GetInstance()->Remove( nullptr );
	EventHandler<EventIndex::OnDrawingRangeIndicator, EventDefines::OnDrawingRangeIndicator, Vector3 *, float, int *, int, float, int, float>::GetInstance()->Add( nullptr );
	EventHandler<EventIndex::OnDrawingRangeIndicator, EventDefines::OnDrawingRangeIndicator, Vector3 *, float, int *, int, float, int, float>::GetInstance()->Remove( nullptr );
	//ObjectManager
	EventHandler<EventIndex::OnGameObjectCreate, EventDefines::OnGameObjectCreate, GameObject*>::GetInstance()->Add( nullptr );
	EventHandler<EventIndex::OnGameObjectCreate, EventDefines::OnGameObjectCreate, GameObject*>::GetInstance()->Remove( nullptr );
	EventHandler<EventIndex::OnGameObjectDelete, EventDefines::OnGameObjectDelete, GameObject*>::GetInstance()->Add( nullptr );
	EventHandler<EventIndex::OnGameObjectDelete, EventDefines::OnGameObjectDelete, GameObject*>::GetInstance()->Remove( nullptr );
	//Obj_AI_Base
	EventHandler<EventIndex::OnObjAIBaseProcessSpell, EventDefines::OnObjAIBaseProcessSpell, Spellbook*, SpellCastInfo*>::GetInstance()->Add( nullptr );
	EventHandler<EventIndex::OnObjAIBaseProcessSpell, EventDefines::OnObjAIBaseProcessSpell, Spellbook*, SpellCastInfo*>::GetInstance()->Remove( nullptr );
	EventHandler<EventIndex::OnObjAIBaseIssueOrder, EventDefines::OnObjAIBaseIssueOrder, GameObject*, EGameObjectOrder, Vector3*, GameObject*, DWORD, DWORD, uint>::GetInstance()->Add( nullptr );
	EventHandler<EventIndex::OnObjAIBaseIssueOrder, EventDefines::OnObjAIBaseIssueOrder, GameObject*, EGameObjectOrder, Vector3*, GameObject*, DWORD, DWORD, uint>::GetInstance()->Remove( nullptr );
	//Player
	/*
	typedef bool(OnPlayerBuyItem)(AIHeroClient*, int, ItemNode*);	10
	typedef bool(OnPlayerSellItem)(AIHeroClient*, int, ItemNode*);	11
	typedef bool(OnPlayerSwapItem)(AIHeroClient*, uint, uint);		12
	typedef bool(OnPlayerDoEmote)(AIHeroClient*, short);			13
	*/

	//Spellbook
	EventHandler<EventIndex::OnSpellbookCastSpell, EventDefines::OnSpellbookCastSpell, Spellbook*, SpellDataInst*, ESpellSlot::ESpellSlot, Vector3*, Vector3*, uint>::GetInstance()->Add( nullptr );
	EventHandler<EventIndex::OnSpellbookCastSpell, EventDefines::OnSpellbookCastSpell, Spellbook*, SpellDataInst*, ESpellSlot::ESpellSlot, Vector3*, Vector3*, uint>::GetInstance()->Remove( nullptr );
	//Chat
	/*typedef bool(OnChatInput)(char**);
	typedef bool(OnChatMessage)(AIHeroClient*, char**);
	typedef bool(OnChatClientSideMessage)(char**);
	typedef bool(OnChatSendWhisper)(char**, char**);*/
}
#pragma endregion


MAKE_HOOK<convention_type::thiscall_r, int, void*, DWORD> MainLoop_Hook;

int __fastcall OnMainLoop( void* a1, DWORD EDX, DWORD a2 )
{
	EventHandler<EventIndex::OnUpdate, EventDefines::OnMainLoop>::GetInstance()->Trigger();

	return MainLoop_Hook.CallOriginal( a1, a2 );
}

bool Game::Initialize()
{
	linkEvents();
	bool status = Patchables::Initialize();

#ifdef _DEBUG_VERSION
	std::cout << "Status : " << std::boolalpha << status << std::endl;
#endif

	return status;
}

bool Game::IsGameFocused()
{
	//return *reinterpret_cast<bool*>(Patchables::LolBase + oIsGameFocused);
	return true;
}

float Game::GetGameTime()
{
	return *reinterpret_cast< float* >( Patchables::LolBase + oGameTime );
}

float Game::GetPing()
{
	return 50;
}

void Game::PrintChat( const char* message )
{
	typedef void( __thiscall* _fnPrintChat )( DWORD ChatClient, const char* Message, int Color );
	static _fnPrintChat oPrintChat = ( _fnPrintChat )( Patchables::LolBase + fnPrintChat );
	static DWORD chatClient = *( DWORD* )( Patchables::LolBase + oChatClientPtr );

	return oPrintChat( chatClient, message, 1);
}

void Game::PrintChat( const char* message, DWORD color ) //0xFF0000FF -> 0x0000FF
{
	char messageBuffer[100];
	int size = sprintf( messageBuffer, "<font color='#%06X'>%s</font>", color & 0x00FFFFFF, message);
	Game::PrintChat( messageBuffer );
}


