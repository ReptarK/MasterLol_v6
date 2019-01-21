#include "SummonerSpells.h"

ESpellSlot::ESpellSlot MasterLol::ActiveSummonerSpell::FindSummonerSpellSlotFromEnum( ESummonerSpell::ESummonerSpell summonerSpellToFind, AIHeroClient * player )
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

void MasterLol::ActiveSummonerSpell::Initialize()
{
	Smite.Slot = FindSummonerSpellSlotFromEnum( ESummonerSpell::SummonerSmite );
	Heal.Slot = FindSummonerSpellSlotFromEnum( ESummonerSpell::SummonerHeal );
	Flash.Slot = FindSummonerSpellSlotFromEnum( ESummonerSpell::SummonerFlash );
	Barrier.Slot = FindSummonerSpellSlotFromEnum( ESummonerSpell::SummonerBarrier );
}
