#pragma once
#include <SDK/StaticEnums.h>
#include <SDK/AIHeroClient.h>
#include <SDK/ObjectManager.h>
#include <SDK/SpellInclude.h>
#include <SDK/singleton.hpp>

namespace Common
{
	class BaseSummonerSpell
	{
	public:
		BaseSummonerSpell()
		{
			Slot = ESpellSlot::Unknown;
			CastType = ESpellCastType::Unknown;
			CastRange = 0;
		}

		ESpellSlot::ESpellSlot Slot;
		ESpellCastType::ESpellCastType CastType;
		float CastRange;
	};

	class Smite
		: public BaseSummonerSpell
	{
	public:
		Smite() : BaseSummonerSpell()
		{
			CastRange = 500;
			CastType = ESpellCastType::Targeted;
		}

		float GetDamage( AIHeroClient* player = ObjectManager::GetPlayer() )
		{
			static float damageArray[18] =
			{ 390, 410, 430, 450, 480, 510,
				540, 570, 600, 640, 680, 720,
				760, 800, 850, 900, 950, 1000,
			};
			return damageArray[*player->GetLevel() - 1];
		}

		bool Cast( AttackableUnit* attackableUnit )
		{
			if ( attackableUnit )
				ObjectManager::GetPlayer()->GetSpellbook()->CastSpell( Slot, attackableUnit->GetPos(), Vector3( 0, 0, 0 ), *attackableUnit->GetNetworkId() );
			return attackableUnit;
		}
	};

	class Heal
		: public BaseSummonerSpell
	{
	public:
		Heal() : BaseSummonerSpell()
		{
			CastType = ESpellCastType::Self;
		}
	};

	class Flash
		: public BaseSummonerSpell
	{
	public:
		Flash() : BaseSummonerSpell()
		{
			CastType = ESpellCastType::Free;
			CastRange = 400;
		}
	};

	class Barrier
		: public BaseSummonerSpell
	{
	public:
		Barrier() : BaseSummonerSpell()
		{
			CastType = ESpellCastType::Self;
		}
	};

	class ActiveSummonerSpell
		: public Singleton<ActiveSummonerSpell>
	{
		friend class Singleton<ActiveSummonerSpell>;
		ActiveSummonerSpell() { this->Initialize(); }
		~ActiveSummonerSpell() {}

	public:
		void Initialize();

		static ESpellSlot::ESpellSlot FindSummonerSpellSlotFromEnum( ESummonerSpell::ESummonerSpell summonerSpellToFind,
			AIHeroClient* player = ObjectManager::GetPlayer() );

		Smite Smite;
		Heal Heal;
		Flash Flash;
		Barrier Barrier;
	};
}
