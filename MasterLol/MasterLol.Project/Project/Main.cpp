#include <Windows.h>
#include <iostream>
#include <stdio.h>

#include <SDK/D3DHooks.h>
#include <SDK/Inputs.h>

#include <Common/MainLoop.h>
#include <Common/ObjectHelper.h>

#include "Component/Components.h"
#include "Menu/Menu.h"
#include "Menu/MenuTab.h"

#include "Test.h"

void InitializeHotkeys()
{
	InputSys::Get().RegisterHotkey(VK_F1, []() {
		TEST::test1();
	});

	InputSys::Get().RegisterHotkey(VK_F2, []() {
		TEST::test2();
	});

	InputSys::Get().RegisterHotkey(VK_F3, []() {
		__try {
			TEST::test3();
		}
		__except (1) { printf("Error in TEST3()"); }
	});

	InputSys::Get().RegisterHotkey(VK_F4, []() {
		__try {
			TEST::test4();
		}
		__except (1) { printf("Error in TEST4()"); }
	});
}

void InitializeConsole()
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
}

void InitializeSDK()
{
	D3D::D3DHooks::Get().Initialize();
	Game::Initialize();
}

void InitializeProject()
{
	Common::ObjectList::Initialize();
	Components::Initialize();
}

DWORD WINAPI MainThread(LPVOID base)
{
	InitializeConsole();
	std::cout << "[ MasterLol Version 6.0 ] \n\n";

	InitializeSDK();

	InputSys::Get().Initialize();
	InitializeHotkeys();

	Menu::Initialize();

	InitializeProject();

	Game::PrintChat("[ MasterLol Version 6.0 ]", BLUE());

	while (!GetAsyncKeyState(VK_END)) {
		MainLoop::Run(1000 / 30);
	}

	Beep(523, 250);

	FreeConsole();
	InputSys::Get().Shutdown();
	D3D::D3DHooks::Get().Shutdown();
	Sleep(250);


	FreeLibraryAndExitThread(static_cast<HMODULE>(base), 1);
	return false;
}

BOOL WINAPI OnDllDetach()
{
	return TRUE;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	switch (reason) {
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
		return TRUE;
	case DLL_PROCESS_DETACH:
		if (lpReserved == nullptr)
			return OnDllDetach();
		return TRUE;
	default:
		return TRUE;
	}
	return TRUE;
}