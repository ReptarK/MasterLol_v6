#pragma once
#include "stdafx.h"
#include "singleton.hpp"

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
	static void PrintChat( const char* Message );
};

