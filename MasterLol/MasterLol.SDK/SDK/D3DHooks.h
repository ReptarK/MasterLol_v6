#pragma once
#include <d3d9.h>
#include "detours/detours.h"
#include "singleton.hpp"
#include "Patchables.h"

namespace D3D
{
	namespace Functions
	{
		// Defines
		using Reset = long(__stdcall *)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
		using Present = long(__stdcall *)(LPDIRECT3DDEVICE9, const RECT*, const RECT*, HWND, const RGNDATA*);
		using EndScene = long(__stdcall *)(IDirect3DDevice9*);

		// Functions
		long __stdcall hkReset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters);
		long __stdcall hkPresent(LPDIRECT3DDEVICE9 pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion);
		long __stdcall hkEndScene(IDirect3DDevice9* device);
	}

	namespace vTableIndex
	{
		constexpr auto Reset = 16;
		constexpr auto Present = 17;
		constexpr auto EndScene = 42;
	}

	class D3DInstance
	{
	public:
		char pad_0000[416]; //0x0000
		LPDIRECT3DDEVICE9 mD3DDevice; //0x01A0
	}; //Size: 0x0244

	class D3DHooks
		: public Singleton<D3DHooks>
	{
		friend class Singleton<D3DHooks>;

		D3DHooks() {}
		~D3DHooks() {}

	public:
		void Initialize();
		void Shutdown();

		//LPDIRECT3DDEVICE9 GetDevice() { return _device; }
		LPDIRECT3DDEVICE9 GetDevice() {
			if (!_device) {
				auto d3dInstance = *(D3DInstance**)(Patchables::LolBase + oD3DInstance);
				printf("D3DInstance : 0X%#x\n", d3dInstance);
				_device = d3dInstance->mD3DDevice;
			}
			return _device;
		}
		void SetDevice(LPDIRECT3DDEVICE9 device) { _device = device; }

		DWORD* D3DVTable;

		Functions::Reset originalReset;
		Functions::Present originalPresent;
		Functions::EndScene originalEndScene;

	private:
		LPDIRECT3DDEVICE9 _device = 0;
	};
}



