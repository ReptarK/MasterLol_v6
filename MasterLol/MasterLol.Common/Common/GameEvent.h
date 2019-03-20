#pragma once
#include <unordered_map>

#include <SDK/singleton.hpp>
#include <SDK/EventManager.h>
#include <SDK/SpellCastInfo.h>
#include <SDK/Obj_AI_Base.h>

namespace Common 
{
	class OnUpdate
	{
	public:
		static void Run(unsigned long long updateFrequency);
	};

	class OnCreateMissile
	{
	public:
		static void AddMissile(MissileClient*);
		static void OnUpdate();
		static void Initialize() 
		{
			mActiveMissileMap = std::unordered_map<MissileClient*, int>();
			EventHandler<EventIndex::OnUpdate, EventDefines::OnMainLoop>::GetInstance()->Add(OnCreateMissile::OnUpdate);
		}
		static std::unordered_map<MissileClient*, int> mActiveMissileMap;
	};

	class OnProcessSpell
	{

	private:
		static void ProcessSpell(SpellCastInfo* activeSpell, Obj_AI_Base* caster);
		static void ProcessHero();
		static void ProcessMinion();
		static void ClearUnactiveSpells();

	public: 
		static std::unordered_map<int, SpellCastInfo*> mActiveProcessSpell;

		static void OnUpdate();
		static void Initialize()
		{
			mActiveProcessSpell = std::unordered_map<int, SpellCastInfo*>();
			EventHandler<EventIndex::OnUpdate, EventDefines::OnMainLoop>::GetInstance()->Add(OnProcessSpell::OnUpdate);
		}
	};
}

