#pragma once
#include "stdafx.h"
#include "singleton.hpp"
#include "colors_define.h"

#define PROCESS_NAME "League of Legends.exe"

class Hook;

class Game
{
	Game() {}
	~Game() {}

public:
	static bool Initialize();
	static void Dump() {};

	static bool IsGameFocused();
	static float GetGameTime();
	static float GetPing();

	static void PrintChat(const char* n);
	static void PrintChat(const char* Message, DWORD color);

	template<typename... Args>
	static void PrintChat(const char* Message, DWORD color, Args...);
};

template<typename ...Args>
inline void Game::PrintChat(const char * message, DWORD color, Args ... args)
{
	char messageBuffer[100];
	sprintf(messageBuffer, message, args...);
	Game::PrintChat(messageBuffer, color);
}
