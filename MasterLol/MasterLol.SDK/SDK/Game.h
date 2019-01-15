#pragma once
#include "stdafx.h"
#include "singleton.hpp"

#define PROCESS_NAME "League of Legends.exe"

class Hook;

class Game
	: public Singleton<Game>
{
	friend class Singleton<Game>;

	Game() {}
	~Game() {}

public:
	bool Initialize();
	void Dump() {};

	bool IsGameFocused();
	float GetGameTime();
	float GetPing();
};

