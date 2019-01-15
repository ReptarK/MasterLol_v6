#pragma once
#include "stdafx.h"

#include "GameObject.h"
#include "AIHeroClient.h"
#include "ObjectManager.h"
#include "Spellbook.h"
#include "EventManager.h"
#include "Game.h"

class TestComponents
{
public:
	static void test()
	{

		if (GetAsyncKeyState(VK_UP))
		{
			AIHeroClient* player = ObjectManager::Get().GetPlayer();
			std::cout << player->GetName() << std::endl;
			std::cout << "AttackDelay : " << player->GetAttackDelay() << std::endl;
			std::cout << "AttackCastDelay : " << player->GetAttackCastDelay() << std::endl;
			std::cout << "AIName : " << player->GetAIName() << std::endl;

			std::cout << "AA speed module : " << player->GetUnitStats()->mAttackSpeedMod << std::endl;
			Game::Get().IsGameFocused();
		}
	}
};
