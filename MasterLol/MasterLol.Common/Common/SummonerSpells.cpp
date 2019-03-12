#include "SummonerSpells.h"

ESpellSlot::ESpellSlot Common::ActiveSummonerSpell::FindSummonerSpellSlotFromEnum( ESummonerSpell::ESummonerSpell summonerSpellToFind, AIHeroClient * player )
{
	SpellData* summoner1 = player->GetSpellbook()->GetSpell( ESpellSlot::Summoner1 )->GetSpellInfo()->GetSpellData();
	SpellData* summoner2 = player->GetSpellbook()->GetSpell( ESpellSlot::Summoner2 )->GetSpellInfo()->GetSpellData();
	auto summonerSpell1 = ESummonerSpell::FromString( summoner1->SpellName );
	auto summonerSpell2 = ESummonerSpell::FromString( summoner2->SpellName );

	if ( summonerSpell1 == summonerSpellToFind )
		return ESpellSlot::Summoner1;
	if ( summonerSpell2 == summonerSpellToFind )
		return ESpellSlot::Summoner2;

	return ESpellSlot::Unknown;
}

void Common::ActiveSummonerSpell::Initialize()
{
	ESummonerSpell::ESummonerSpell smiteEnums[] = {
		ESummonerSpell::SummonerSmite,
		ESummonerSpell::S5_SummonerSmiteDuel,
		ESummonerSpell::S5_SummonerSmitePlayerGanker
	};

	for (int i = 0; i < 3 && Smite.Slot == ESpellSlot::Unknown; ++i)
		Smite.Slot = FindSummonerSpellSlotFromEnum(smiteEnums[i]);

	Heal.Slot = FindSummonerSpellSlotFromEnum( ESummonerSpell::SummonerHeal );
	Flash.Slot = FindSummonerSpellSlotFromEnum( ESummonerSpell::SummonerFlash );
	Barrier.Slot = FindSummonerSpellSlotFromEnum( ESummonerSpell::SummonerBarrier );
}
