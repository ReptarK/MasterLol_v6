#pragma once
#include <SDK/ObjectManager.h>
#include <SDK/SpellCastInfo.h>
#include <SDK/Draw.h>

#include <SDK/EventManager.h>

#define LINE_WIDTH 55

class DebugComponent
{
public:
	static GameObject * selectedtarget;

	static void Initialize();

	~DebugComponent()
	{
		EventHandler<EventIndex::OnDrawingEndScene, EventDefines::OnDrawingEndScene, IDirect3DDevice9*>::GetInstance()->Remove(DebugComponent::OnEndScene);
		EventHandler<EventIndex::OnMainLoop, EventDefines::OnMainLoop>::GetInstance()->Remove(DebugComponent::OnUpdate);
	}

private:
	// Events
	static void OnUpdate();
	static void OnEndScene(IDirect3DDevice9*);
};
