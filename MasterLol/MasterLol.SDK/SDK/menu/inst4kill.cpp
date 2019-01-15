#define WIN32_LEAN_AND_MEAN
#define VC_EXTRA_LEAN

#include "draw.h"
#include "input.h"
#include "menu.h"
#include "tools.h"

DWORD* FindVTable();

string onOff[]		= { "Off", "On" };
string aimBone[]	= { "Torso", "Upper Torso", "Head", "Neck", "Nuts" };
string aimAngle[]	= { "360", "180", "90", "45", "30", "15" };
string multiplier[]	= { "Off", "x1", "x2", "x3", "x4", "x5", "x6", "x7", "x8", "x9", "x10" };
string aimTime[]	= { "Instant", "100ms", "200ms", "300ms", "400ms", "500ms", "600ms", "700ms", "800ms", "900ms", "1000ms" };
string keys[]		= { "LClick", "MClick", "RClick", "Alt", "Ctrl", "Shift" };

string moduleList[] = { "d3d9.dll" };

void InitializeMenu()
{
	menu.Header("inst4kill - Premium");

	menu.AddTab("Visual");
	menu.AddItem("Chams", onOff);
	menu.AddItem("No Fog", onOff);
	menu.AddItem("Crosshair", onOff);
	menu.AddItem("Name ESP", onOff);
	menu.AddItem("Box ESP", onOff);
	menu.AddItem("Line ESP", onOff);
	menu.AddItem("Distance ESP", onOff);
	menu.AddItem("Health ESP", onOff);
	menu.AddItem("Skeleton ESP", onOff);
	menu.AddItem("Explosive ESP", onOff);
	menu.AddItem("Pickup ESP", onOff);
	menu.AddItem("All Players", onOff);

	menu.AddTab("Aimbot");
	menu.AddItem("Aimbot", onOff);
	menu.AddItem("Aim Key", keys, 6);
	menu.AddItem("Aim Bone", aimBone, 5);
	menu.AddItem("Auto Switch", onOff);
	menu.AddItem("Aim Angle", aimAngle, 6);
	menu.AddItem("Smooth Aim", aimTime, 11);
	menu.AddItem("Aim Thru Walls", onOff);
	menu.AddItem("Friendly Fire", onOff);
	menu.AddItem("Off After Kill", onOff);

	menu.AddTab("Stats");
	menu.AddItem("Recoil Control", multiplier, 11);
	menu.AddItem("Spread Control", multiplier, 11);
	menu.AddItem("Rapid Fire", onOff);
	menu.AddItem("Far Pickup", onOff);
	menu.AddItem("Fly Mode", onOff);
	menu.AddItem("Super Speed", multiplier, 11);
	menu.AddItem("Super Jump", multiplier, 11);

	menu.AddTab("Misc");
	menu.AddItem("Super Pickup", onOff);
	menu.AddItem("Free Run", onOff);
	menu.AddItem("Head Glitch", onOff);
	menu.AddItem("Chat Spam", onOff);
	menu.AddItem("Voice Spam", onOff);
	menu.AddItem("Ghost Mode", onOff);
	menu.AddItem("Glitcher Mode", onOff);
	menu.AddItem("Tele Kill", onOff);
}

typedef HRESULT (WINAPI* oPresent)(LPDIRECT3DDEVICE9 pDevice, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion);
oPresent pPresent;

HRESULT WINAPI hkPresent(LPDIRECT3DDEVICE9 pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{
	if (!draw.IsInitialized())
	{
		draw.SetDevice(pDevice);
		D3DXCreateFontA(draw.GetDevice(), 16, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Calibri", &draw.font);
		
		input.Init();
		draw.Init();
	}

	draw.GetDevice()->GetViewport(&draw.viewport);

	draw.GetDevice()->SetTexture(NULL, NULL);
	draw.GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DZB_TRUE);
	draw.GetDevice()->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	draw.GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	input.Update();
	menu.Render();

	draw.GetDevice()->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

	return pPresent(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

DWORD CALLBACK MainThread(LPVOID lpArgs)
{
	while (!tools.IsReadyForHook(moduleList, GetSizeOf(moduleList)))
		Sleep(25);

	InitializeMenu();

	DWORD* pVTable = FindVTable();
	pPresent = (oPresent)tools.DetourFunction((PBYTE)pVTable[17], (PBYTE)&hkPresent, 5);

	return EXIT_SUCCESS;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, 0, 0, 0);
	}
	return TRUE;
}

static LRESULT CALLBACK MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

DWORD* FindVTable()
{
	WNDCLASSEX wc = {sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, "DX", NULL};
	RegisterClassEx(&wc);
	HWND hWnd = CreateWindowA("DX", NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, GetDesktopWindow(), NULL, wc.hInstance, NULL);

	LPDIRECT3D9 pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS presentParameters; 
	ZeroMemory(&presentParameters, sizeof(presentParameters));
	presentParameters.Windowed = TRUE;
	presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentParameters.BackBufferFormat = D3DFMT_UNKNOWN;

	LPDIRECT3DDEVICE9 pDevice;
	pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &presentParameters, &pDevice);

	DWORD* pVTable = (DWORD*)pDevice;
	pVTable = (DWORD*)pVTable[0];
	DestroyWindow(hWnd);
	return pVTable;
}