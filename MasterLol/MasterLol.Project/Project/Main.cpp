#include <Windows.h>
#include <iostream>
#include <stdio.h>

#include <SDK/D3DHooks.h>
#include <SDK/Inputs.h>
#include <SDK/Config.h>

#include <Common/GameEvent.h>
#include <Common/ObjectHelper.h>

#include "Menu/Menu.h"

#include "Component/ComponentsManager.h"
#include "Component/Visual.component/Visual.component.h"
#include "Component/Debug.component/Debug.component.h"
#include "Component/SummonerSpell.component/SummonerSpell.component.h"
#include "Component/Orbwalker.component/Orbwalker.component.h"

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

	InputSys::Get().RegisterHotkey(VK_F5, []() {
		__try {
			TEST::test5();
		}
		__except (1) { printf("Error in TEST5()"); }
	});

	InputSys::Get().RegisterHotkey(VK_F6, []() {
		TEST::testNavigation();
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
	Game::Initialize();
	D3D::D3DHooks::Get().Initialize();
}

void InitializeProject()
{
	Common::ObjectList::Initialize();

	ComponentsManager::Initialize();
	ComponentsManager::AddComponent<VisualComponent>();
	ComponentsManager::AddComponent<DebugComponent>();
	ComponentsManager::AddComponent<SummonerSpellComponent>();
	ComponentsManager::AddComponent<OrbwalkerComponent>();
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

	Common::OnProcessSpell::Initialize();
	while (!GetAsyncKeyState(VK_END)) {
		Common::OnUpdate::Run(1000 / 30);
	}
	g_Unload = true;
	D3D::D3DHooks::Get().Shutdown();
	Sleep(500);

	Beep(523, 250);
	FreeConsole();
	ComponentsManager::Shutdown();
	InputSys::Get().Shutdown();
	Sleep(250);
	Draw.FontRelease();

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