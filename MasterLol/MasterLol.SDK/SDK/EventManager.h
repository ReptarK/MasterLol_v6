#pragma once
#include <vector>
#include "Macros.h"
#include <functional>
#include "GameObject.h"
#include "SpellCastInfo.h"
#include "Obj_AI_Base.h"
#include "AttackableUnit.h"
#include "AIHeroClient.h"
#include "SpellDataInst.h"
#include <d3d9.h>

#ifndef N_MANAGED_BUILD
#include <ppl.h>
#include <future>
#endif


#define EVENT_TIMEOUT_EJECT 250

enum class EventIndex
{
	OnUpdate = 1,
	OnDrawingEndScene = 2,
	OnReset = 3,
	OnDrawingPresent = 4,
	OnDrawingRangeIndicator = 5,
	OnGameObjectCreate = 6,
	OnGameObjectDelete = 7,
	OnObjAIBaseProcessSpell = 8,
	OnObjAIBaseIssueOrder = 9,
	OnSpellbookCastSpell = 14,

	OnCreateMissile = 15,
	OnProcessSpell = 16
};

namespace EventDefines
{
	class ItemNode;

	//Game
	typedef void( OnMainLoop )();
	typedef void (OnCreateMissile)(MissileClient*, Obj_AI_Base*);
	typedef void (OnProcessSpell)(SpellCastInfo*, Obj_AI_Base*);

	//Drawing
	typedef void( OnDrawingEndScene )( IDirect3DDevice9* );
	typedef void( OnReset )( IDirect3DDevice9*, D3DPRESENT_PARAMETERS* );
	typedef void( OnDrawingPresent )( LPDIRECT3DDEVICE9, const RECT*, const RECT*, HWND, const RGNDATA* );
	typedef void( OnDrawingRangeIndicator )( Vector3* position, float range, int* color, int, float, int, float alpha );

	//ObjectManager
	typedef void( OnGameObjectCreate )( GameObject* );
	typedef int( OnGameObjectDelete )( GameObject* );

	//Obj_AI_Base
	typedef bool( OnObjAIBaseProcessSpell )( Spellbook* spellbook, SpellCastInfo* );
	typedef bool( OnObjAIBaseIssueOrder )( GameObject*, EGameObjectOrder, Vector3*, GameObject*, DWORD, DWORD, uint );

	//AIHeroClient

	//Player
	typedef bool( OnPlayerBuyItem )( AIHeroClient*, int, ItemNode* );
	typedef bool( OnPlayerSellItem )( AIHeroClient*, int, ItemNode* );
	typedef bool( OnPlayerSwapItem )( AIHeroClient*, uint, uint );
	typedef bool( OnPlayerDoEmote )( AIHeroClient*, short );

	//Spellbook
	typedef bool( OnSpellbookCastSpell )( Spellbook*, SpellDataInst*, ESpellSlot::ESpellSlot, Vector3*, Vector3*, uint );

	//Chat
	typedef bool( OnChatInput )( char** );
	typedef bool( OnChatMessage )( AIHeroClient*, char** );
	typedef bool( OnChatClientSideMessage )( char** );
	typedef bool( OnChatSendWhisper )( char**, char** );
}


// ReSharper disable once CppClassNeedsConstructorBecauseOfUninitializedMember
template <EventIndex uniqueEventNumber, typename T, typename ... TArgs>
class EventHandler
{
	std::vector<void*> m_EventCallbacks;
	DWORD t_RemovalTickCount;
	static EventHandler* instance;
public:
	static EventHandler* GetInstance()
	{
		if ( instance == nullptr )
		{
			instance = new EventHandler();
		}

		return instance;
	}

	void Add( void* callback )
	{
		if ( callback != nullptr )
		{
			m_EventCallbacks.push_back( callback );
		}
	}

	void Remove( void* listener )
	{
		if ( listener == nullptr )
		{
			return;
		}

		auto eventPtr = find( m_EventCallbacks.begin(), m_EventCallbacks.end(), listener );
		if ( eventPtr != m_EventCallbacks.end() )
		{
			m_EventCallbacks.erase( find( m_EventCallbacks.begin(), m_EventCallbacks.end(), listener ) );
		}

		this->t_RemovalTickCount = GetTickCount();
	}

	bool __cdecl TriggerProcess( TArgs... args )
	{
		auto process = true;
		auto tickCount = GetTickCount();

		for ( auto ptr : m_EventCallbacks )
		{
			if ( ptr != nullptr )
			{
				if ( tickCount - t_RemovalTickCount > EVENT_TIMEOUT_EJECT )
				{
					if ( !static_cast< T* >( ptr ) ( args... ) )
					{
						process = false;
					}
				}
			}
		}

		return process;
	}

	bool __cdecl Trigger( TArgs... args )
	{
		auto tickCount = GetTickCount();

		for ( auto ptr : m_EventCallbacks )
		{
			if ( ptr != nullptr )
			{
				if ( tickCount - t_RemovalTickCount > EVENT_TIMEOUT_EJECT )
				{
					static_cast< T* >( ptr ) ( args... );
				}
			}
		}

		return true;
	}
};

