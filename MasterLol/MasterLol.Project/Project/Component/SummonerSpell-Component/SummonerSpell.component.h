#pragma once
#include <SDK/EventManager.h>

class SummonerSpellComponent
{
public:
	static GameObject * selectedtarget;

	static void Initialize();

	~SummonerSpellComponent()
	{
		EventHandler<EventIndex::OnDrawingEndScene, EventDefines::OnDrawingEndScene, IDirect3DDevice9*>::GetInstance()->Remove(SummonerSpellComponent::OnEndScene);
		EventHandler<EventIndex::OnMainLoop, EventDefines::OnMainLoop>::GetInstance()->Remove(SummonerSpellComponent::OnUpdate);
	}

private:
	// Events
	static void OnUpdate();
	static void OnEndScene(IDirect3DDevice9*);
};
