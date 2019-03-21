#include "GameEvent.h"
#include <chrono>
#include <iostream>
#include <thread>

#include <SDK/EventManager.h>
#include <SDK/Game.h>
#include <SDK/SpellInclude.h>

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


	std::unordered_map<MissileClient*, int> OnCreateMissile::mActiveMissileMap;
	void OnCreateMissile::AddMissile(MissileClient * missile)
	{
		std::pair<MissileClient*, int> newMissile(missile, missile->GetCreatedTimeMs());
		mActiveMissileMap.insert(newMissile);
	}

	void OnCreateMissile::OnUpdate()
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
				EventHandler<EventIndex::OnCreateMissile, EventDefines::OnCreateMissile,
					MissileClient*, Obj_AI_Base*>::GetInstance()->Trigger(missile, caster);
				return;
			}
			if (got->second < missile->GetCreatedTimeMs())
			{
				got->second = missile->GetCreatedTimeMs();
				auto caster = (Obj_AI_Base*)ObjectHelper::GetSourceObject(missile);
				EventHandler<EventIndex::OnCreateMissile, EventDefines::OnCreateMissile,
					MissileClient*, Obj_AI_Base*>::GetInstance()->Trigger(missile, caster);
				return;
			}
		}
	}

	/////// OnMissileProcessSpell ///////
	std::unordered_map<int, SpellCastInfo*> OnProcessSpell::mActiveProcessSpell;

	void OnProcessSpell::ProcessHero()
	{
		auto allHero = ObjectList::mAllHeros;
		for (Obj_AI_Base* hero : allHero)
		{
			Spellbook* spellbook = hero->GetSpellbook();
			if (!spellbook) continue;

			SpellCastInfo* activeSpell = spellbook->GetActiveSpell();
			if (!activeSpell) continue;

			OnProcessSpell::ProcessSpell(activeSpell, hero);
		}
	}

	void OnProcessSpell::ProcessMinion()
	{
		auto allMinion = ObjectList::mAllMinions;
		for (Obj_AI_Base* minion : allMinion)
		{
			Spellbook* spellbook = minion->GetSpellbook();
			if (!spellbook) continue;

			SpellCastInfo* activeSpell = spellbook->GetActiveSpell();
			if (!activeSpell) continue;

			OnProcessSpell::ProcessSpell(activeSpell, minion);
		}
	}

	void OnProcessSpell::ProcessSpell(SpellCastInfo * activeSpell, Obj_AI_Base* caster)
	{
		auto got = mActiveProcessSpell.find(activeSpell->GetUniqueId());
		if (got != mActiveProcessSpell.end()) {
			// Already Processed
			return;
		}

		std::pair<int, SpellCastInfo*> newProcessSpell(activeSpell->GetUniqueId(), activeSpell);

		mActiveProcessSpell.insert(newProcessSpell);

		EventHandler<EventIndex::OnProcessSpell, EventDefines::OnProcessSpell,
			SpellCastInfo*, Obj_AI_Base*>::GetInstance()->Trigger(activeSpell, caster);
	}

	void OnProcessSpell::ClearUnactiveSpells()
	{
		for (auto it = mActiveProcessSpell.begin(); it != mActiveProcessSpell.end(); ) {
			if (Game::GetGameTime() > it->second->mEndTime) {
				it = mActiveProcessSpell.erase(it);
			}
			else
				it++;
		}
	}

	void OnProcessSpell::OnUpdate()
	{
		OnProcessSpell::ProcessHero();
		OnProcessSpell::ProcessMinion();

		OnProcessSpell::ClearUnactiveSpells();
	}
}

