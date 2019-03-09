#include "SummonerSpell.component.h"

#include <SDK/Options.h>
#include <Common/SummonerSpells.h>

void SummonerSpellComponent::Initialize()
{
	EventHandler<EventIndex::OnDrawingEndScene, EventDefines::OnDrawingEndScene, IDirect3DDevice9*>::GetInstance()->Add(SummonerSpellComponent::OnEndScene);
	EventHandler<EventIndex::OnMainLoop, EventDefines::OnMainLoop>::GetInstance()->Add(SummonerSpellComponent::OnUpdate);
}

void SummonerSpellComponent::OnUpdate()
{
	if (g_Options.enable_auto_smite)
	{

	}
}

void SummonerSpellComponent::OnEndScene(IDirect3DDevice9* device)
{
}
