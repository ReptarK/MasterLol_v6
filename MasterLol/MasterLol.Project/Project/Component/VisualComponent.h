#pragma once
#include <SDK/EventManager.h>
#include "IComponent.h"

class VisualComponent : public IComponent
{
	static void OnEndScene( LPDIRECT3DDEVICE9 device );

	static void Shutdown()
	{
		EventHandler<EventIndex::OnDrawingEndScene, EventDefines::OnDrawingEndScene, IDirect3DDevice9*>::GetInstance()->Remove( VisualComponent::OnEndScene );
	}

public:
	static void Initialize();
};
