#include "stdafx.h"
#include "D3DHooks.h"

#include "Utilities.h"
//#include "menu/menu.h"
#include "Draw.h"
#include "Options.h"
#include "EventManager.h"

namespace D3D
{
	namespace Functions
	{
		long __stdcall hkReset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters)
		{
			EventHandler<EventIndex::OnReset, EventDefines::OnReset, IDirect3DDevice9*, D3DPRESENT_PARAMETERS*>::GetInstance()->Trigger(device, pPresentationParameters);
			auto hr = D3DHooks::Get().originalReset(device, pPresentationParameters);
			/**/
			return hr;
		}

		long __stdcall hkPresent(LPDIRECT3DDEVICE9 pDevice, const RECT* pSourceRect, const RECT* pDestRect,
			HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
		{
			if (!g_Unload)
			{
				if (!D3DHooks::Get().GetDevice())
					D3DHooks::Get().SetDevice(pDevice);
			}

			EventHandler<EventIndex::OnDrawingPresent, EventDefines::OnDrawingPresent, LPDIRECT3DDEVICE9, const RECT*, const RECT*, HWND, const RGNDATA*>
				::GetInstance()->Trigger(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
			return D3DHooks::Get().originalPresent(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
		}

		long __stdcall hkEndScene(IDirect3DDevice9* device)
		{
			EventHandler<EventIndex::OnDrawingEndScene, EventDefines::OnDrawingEndScene, IDirect3DDevice9*>::GetInstance()->Trigger(device);
			return D3DHooks::Get().originalEndScene(device);
		}
	}

	void D3DHooks::Initialize()
	{
		DWORD table = PatternScanning::FindPattern((DWORD)GetModuleHandle(L"d3d9.dll"), 0x128000,
			(PBYTE)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86", "xx????xx????xx");
		memcpy(&D3DVTable, (void*)(table + 2), 4);

		originalReset = (Functions::Reset)DetourFunction((PBYTE)D3DVTable[D3D::vTableIndex::Reset], (PBYTE)Functions::hkReset);
		originalPresent = (Functions::Present)DetourFunction((PBYTE)D3DVTable[vTableIndex::Present], (PBYTE)Functions::hkPresent);
		originalEndScene = (Functions::EndScene)DetourFunction((PBYTE)D3DVTable[vTableIndex::EndScene], (PBYTE)Functions::hkEndScene);
	}

	void D3DHooks::Shutdown()
	{
		if (originalReset)
			(Functions::Reset)DetourRemove((PBYTE)originalReset, (PBYTE)(PBYTE)Functions::hkReset);

		if (originalPresent)
		{
			(Functions::Present)DetourRemove((PBYTE)originalPresent, (PBYTE)(PBYTE)Functions::hkPresent);
		}

		if (originalEndScene)
		{
			(Functions::EndScene)DetourRemove((PBYTE)originalEndScene, (PBYTE)(PBYTE)Functions::hkEndScene);
			Draw.FontRelease();
		}
	}
}

