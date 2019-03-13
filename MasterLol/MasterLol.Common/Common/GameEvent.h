#pragma once
#include <unordered_map>

#include <SDK/singleton.hpp>
#include <SDK/EventManager.h>

namespace Common 
{
	class OnUpdate
	{
	public:
		static void Run(unsigned long long updateFrequency);
	};

	class OnMissileProcessSpell
	{
	public:
		static void AddMissile(MissileClient*);
		static void OnUpdate();
		static void Initialize() 
		{
			mActiveMissileMap = std::unordered_map<MissileClient*, int>();
			EventHandler<EventIndex::OnUpdate, EventDefines::OnMainLoop>::GetInstance()->Add(OnMissileProcessSpell::OnUpdate);
		}
		static std::unordered_map<MissileClient*, int> mActiveMissileMap;
	};
}

