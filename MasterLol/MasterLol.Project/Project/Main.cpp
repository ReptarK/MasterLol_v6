#include <Windows.h>
#include <iostream>
#include <stdio.h>

#include <SDK/D3DHooks.h>
#include <SDK/Inputs.h>

#include <Common/MainLoop.h>
#include <Common/Menu/Menu.h>

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

void InitializeProject()
{
	D3D::D3DHooks::Get().Initialize();
	Game::Initialize();
}

DWORD WINAPI MainThread( LPVOID base )
{
	InitializeConsole();
	std::cout << "[ MasterLol Version 6.0 ] \n\n";

	InitializeProject();

	InputSys::Get().Initialize();
	InitializeHotkeys();

	Menu::Initialize();

	while ( !GetAsyncKeyState( VK_END ) ) {
		MainLoop::Run( 33 );
	}

	Beep( 523, 250 );
	FreeConsole();
	Sleep( 250 );
	FreeLibraryAndExitThread( static_cast< HMODULE >( base ), 1 );
	return false;
}

BOOL WINAPI OnDllDetach()
{
	D3D::D3DHooks::Get().Shutdown();
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