#include "GameEvent.h"
#include <chrono>
#include <iostream>
#include <thread>

#include <SDK/EventManager.h>

#include "ObjectHelper.h"

namespace Common
{
	void OnUpdate::Run(unsigned long long updateFrequency)
	{
		using namespace std::chrono;
		static auto updateFreq = std::chrono::milliseconds(updateFrequency);
		static auto next = steady_clock::now();
		static auto prev = next - updateFreq;

		auto now = steady_clock::now();
		prev = now;

		EventHandler<EventIndex::OnUpdate, EventDefines::OnMainLoop>::GetInstance()->Trigger();

		next += updateFreq;
		std::this_thread::sleep_until(next);
	}




	std::unordered_map<MissileClient*, int> OnMissileProcessSpell::mActiveMissileMap;
	void OnMissileProcessSpell::AddMissile(MissileClient * missile)
	{
		std::pair<MissileClient*, int> newMissile(missile, missile->GetCreatedTimeMs());
		mActiveMissileMap.insert(newMissile);
	}

	void OnMissileProcessSpell::OnUpdate()
	{
		auto allMissile = ObjectList::mAllMissiles;
		for (auto missile : allMissile)
		{
			auto got = mActiveMissileMap.find(missile);
			if (got == mActiveMissileMap.end())
			{
				// Not Found
				AddMissile(missile);

				auto caster = (Obj_AI_Base*)ObjectHelper::GetSourceObject(missile);
				EventHandler<EventIndex::OnMissileProcessSpell, EventDefines::OnMissileProcessSpell,
					MissileClient*, GameObject*>::GetInstance()->Trigger(missile, caster);
				return;
			}
			if (got->second < missile->GetCreatedTimeMs())
			{
				got->second = missile->GetCreatedTimeMs();
				auto caster = (Obj_AI_Base*)ObjectHelper::GetSourceObject(missile);
				EventHandler<EventIndex::OnMissileProcessSpell, EventDefines::OnMissileProcessSpell,
					MissileClient*, GameObject*>::GetInstance()->Trigger(missile, caster);
				return;
			}
		}
	}
}

