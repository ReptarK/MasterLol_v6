#include "stdafx.h"
#include "D3DHooks.h"

#include "Utilities.h"
//#include "menu/menu.h"
#include "Draw.h"
#include "Config.h"
#include "EventManager.h"
#include "Draw.h"

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

namespace D3D
{
	namespace Functions
	{
		long __stdcall hkReset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters)
		{
			Draw.OnLostDevice();

			EventHandler<EventIndex::OnReset, EventDefines::OnReset, IDirect3DDevice9*, D3DPRESENT_PARAMETERS*>::GetInstance()->Trigger(device, pPresentationParameters);
			auto hr = D3DHooks::Get().originalReset(device, pPresentationParameters);

			if (hr == D3D_OK)
				Draw.OnResetDevice();

			return hr;
		}

		long __stdcall hkPresent(LPDIRECT3DDEVICE9 pDevice, const RECT* pSourceRect, const RECT* pDestRect,
			HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
		{
			if (g_Unload)
				return D3DHooks::Get().originalEndScene(pDevice);

			if (!D3DHooks::Get().GetDevice())
				D3DHooks::Get().SetDevice(pDevice);

			if (!Draw.Screen.Width) {
				Draw.SetScreenInfo();
			}

			Draw.Text("MasterLol", Draw.Screen.x_center, 0, centered, 0, false, RED());

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

	LRESULT CALLBACK D3D9MsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { return DefWindowProc(hwnd, uMsg, wParam, lParam); }

	void D3DHooks::Initialize()
	{
		HMODULE dDll_ = NULL;
		while (!dDll_)
		{
			dDll_ = GetModuleHandleA("d3d9.dll");
			Sleep(100);
		}
		CloseHandle(dDll_);

		printf("D3DDevice : 0X%#x \n", D3DHooks::Get().GetDevice());
		D3DVTable = *(DWORD**)D3DHooks::Get().GetDevice();

		std::cout << "Table at : ";
		printf("0x%08x\n", D3DVTable);

		originalReset = (Functions::Reset)DetourFunction((PBYTE)D3DVTable[D3D::vTableIndex::Reset], (PBYTE)Functions::hkReset);
		originalPresent = (Functions::Present)DetourFunction((PBYTE)D3DVTable[vTableIndex::Present], (PBYTE)Functions::hkPresent);
		originalEndScene = (Functions::EndScene)DetourFunction((PBYTE)D3DVTable[vTableIndex::EndScene], (PBYTE)Functions::hkEndScene);

	}

	//	void D3DHooks::Initialize()
	//	{
	//		//DWORD table = PatternScanning::FindPattern((DWORD)GetModuleHandle(L"d3d9.dll"), 0x128000,
	//		//	(PBYTE)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86", "xx????xx????xx");
	//		//memcpy(&D3DVTable, (void*)(table + 2), 4);
	//
	//		HMODULE dDll_ = NULL;
	//		while (!dDll_)
	//		{
	//			dDll_ = GetModuleHandleA("d3d9.dll");
	//			Sleep(100);
	//		}
	//		CloseHandle(dDll_);
	//
	//		IDirect3D9* d3d = NULL;
	//		IDirect3DDevice9* d3ddev = NULL;
	//
	//		std::cout << "[GetModuleHandleA(NULL)] = " << GetModuleHandleA(NULL) << std::endl;
	//
	//		WNDCLASSEXA wc = { sizeof(WNDCLASSEX),CS_CLASSDC,D3D9MsgProc,0L,0L,GetModuleHandleA(NULL),NULL,NULL,NULL,NULL,"DX",NULL };
	//		RegisterClassExA(&wc);
	//		std::cout << "[WNDCLASSEXA] = " << &wc << std::endl;
	//		HWND tmpWnd = CreateWindowA("DX", NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, GetDesktopWindow(), NULL, wc.hInstance, NULL);
	//		if (tmpWnd == NULL)
	//		{
	//			std::cout << "[DirectX] Failed to create temp window" << std::endl;
	//			return;
	//		}
	//
	//		d3d = Direct3DCreate9(D3D_SDK_VERSION);
	//		if (d3d == NULL)
	//		{
	//			DestroyWindow(tmpWnd);
	//			std::cout << "[DirectX] Failed to create temp Direct3D interface" << std::endl;
	//			return;
	//		}
	//
	//		D3DPRESENT_PARAMETERS d3dpp;
	//		ZeroMemory(&d3dpp, sizeof(d3dpp));
	//		d3dpp.Windowed = TRUE;
	//		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	//		d3dpp.hDeviceWindow = tmpWnd;
	//		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	//
	//		HRESULT result = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, tmpWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);
	//		if (result != D3D_OK)
	//		{
	//			d3d->Release();
	//			DestroyWindow(tmpWnd);
	//			std::cout << "[DirectX] Failed to create temp Direct3D device" << std::endl;
	//			return;
	//		}
	//		std::cout << "[d3ddev] = " << d3ddev << std::endl;
	//#if defined _M_X64
	//		DWORD64* dVtable_ = (DWORD64*)d3ddev;
	//		dVtable_ = (DWORD64*)dVtable_[0];
	//#elif defined _M_IX86
	//		DWORD* dVtable_ = (DWORD*)d3ddev;
	//		dVtable_ = (DWORD*)dVtable_[0]; // == *d3ddev
	//#endif
	//
	//		D3DVTable = dVtable_;
	//		DestroyWindow(tmpWnd);
	//
	//		std::cout << "Table at : ";
	//		printf("0x%08x\n", D3DVTable);
	//
	//		originalReset = (Functions::Reset)DetourFunction((PBYTE)D3DVTable[D3D::vTableIndex::Reset], (PBYTE)Functions::hkReset);
	//		originalPresent = (Functions::Present)DetourFunction((PBYTE)D3DVTable[vTableIndex::Present], (PBYTE)Functions::hkPresent);
	//		originalEndScene = (Functions::EndScene)DetourFunction((PBYTE)D3DVTable[vTableIndex::EndScene], (PBYTE)Functions::hkEndScene);
	//	}

	void D3DHooks::Shutdown()
	{
		//delete EventHandler<EventIndex::OnDrawingEndScene, EventDefines::OnDrawingEndScene, IDirect3DDevice9*>::GetInstance();
		//delete EventHandler<EventIndex::OnReset, EventDefines::OnReset, IDirect3DDevice9*, D3DPRESENT_PARAMETERS*>::GetInstance();
		//delete EventHandler<EventIndex::OnDrawingPresent, EventDefines::OnDrawingPresent, LPDIRECT3DDEVICE9, const RECT*, const RECT*, HWND, const RGNDATA*>
		//	::GetInstance();
		//EventHandler<EventIndex::OnUpdate, EventDefines::OnMainLoop>::GetInstance();

		if (originalReset)
			(Functions::Reset)DetourRemove((PBYTE)originalReset, (PBYTE)Functions::hkReset);

		if (originalPresent)
		{
			(Functions::Present)DetourRemove((PBYTE)originalPresent, (PBYTE)Functions::hkPresent);
		}

		if (originalEndScene)
		{
			(Functions::EndScene)DetourRemove((PBYTE)originalEndScene, (PBYTE)Functions::hkEndScene);
			Draw.FontRelease();
		}
	}
}

