#pragma once
#include <SDK/EventManager.h>

class BasicVisuals
{
	static void OnEndScene( LPDIRECT3DDEVICE9 device );

	~BasicVisuals()
	{
		EventHandler<EventIndex::OnDrawingEndScene, EventDefines::OnDrawingEndScene, IDirect3DDevice9*>::GetInstance()->Remove( BasicVisuals::OnEndScene );
	}

public:
	static void Initialize();
};
