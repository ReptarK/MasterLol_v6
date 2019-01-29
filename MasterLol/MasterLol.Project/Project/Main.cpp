#include <Windows.h>
#include <iostream>
#include <stdio.h>

#include <SDK/D3DHooks.h>
#include <SDK/Inputs.h>

#include <Common/MainLoop.h>
#include <Common/Menu/Menu.h>
#include "Component/Components.h"

#include "Test.h"

void InitializeHotkeys()
{
	InputSys::Get().RegisterHotkey( VK_HOME, []() {
		Menu::Toggle();
	} );

	InputSys::Get().RegisterHotkey( VK_F1, []() {
		TEST::test1();
	} );

	InputSys::Get().RegisterHotkey( VK_F2, []() {
		TEST::test2();
	} );

	InputSys::Get().RegisterHotkey( VK_F3, []() {
		TEST::test3();
	} );
}

void InitializeConsole()
{
	AllocConsole();
	freopen( "CONOUT$", "w", stdout );
}

void InitializeSDK()
{
	D3D::D3DHooks::Get().Initialize();
	Game::Initialize();
}

void InitializeProject()
{
	Components::Initialize();
}

DWORD WINAPI MainThread( LPVOID base )
{
	InitializeConsole();
	std::cout << "[ MasterLol Version 6.0 ] \n\n";

	InitializeSDK();

	InputSys::Get().Initialize();
	InitializeHotkeys();

	Menu::Initialize();
	InitializeProject();

	while ( !GetAsyncKeyState( VK_END ) ) {
		MainLoop::Run( 1000 / 30 );
	}

	Beep( 523, 250 );

	FreeConsole();
	Sleep( 250 );

	InputSys::Get().Shutdown();
	D3D::D3DHooks::Get().Shutdown();

	FreeLibraryAndExitThread( static_cast< HMODULE >( base ), 1 );
	return false;
}

BOOL WINAPI OnDllDetach()
{
	//InputSys::Get().Shutdown();
	//D3D::D3DHooks::Get().Shutdown();
	return TRUE;
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD reason, LPVOID lpReserved )
{
	switch ( reason ) {
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls( hModule );
		CreateThread( nullptr, 0, MainThread, hModule, 0, nullptr );
		return TRUE;
	case DLL_PROCESS_DETACH:
		if ( lpReserved == nullptr )
			return OnDllDetach();
		return TRUE;
	default:
		return TRUE;
	}
	return TRUE;
}