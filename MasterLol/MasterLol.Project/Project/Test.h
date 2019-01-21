#pragma once
#include <SDK/Game.h>
#include <SDK/colors_define.h>
#include <SDK/ObjectManager.h>
#include <SDK/AIHeroClient.h>
#include <Common/GameFunctions.h>
#include <SDK/HudManager.h>

namespace TEST
{
	static void test1()
	{
		// LocalPlayer
		printf( "LocalPlayer : %#x \n", ObjectManager::GetPlayer() );
		printf( "\t AI Manager : %#x \n", ObjectManager::GetPlayer()->GetAIManager() );
		printf( "\t Name : %s \n", ObjectManager::GetPlayer()->GetName().c_str() );
		printf( "\t Position : (%.0f, %.0f, %.0f) \n",
			ObjectManager::GetPlayer()->GetPos().x,
			ObjectManager::GetPlayer()->GetPos().y,
			ObjectManager::GetPlayer()->GetPos().z );
		printf( "\t BoundingRadius : %.0f \n", ObjectManager::GetPlayer()->GetBoundingRadius() );
		printf( "IsHero : %s\n", ObjectManager::GetPlayer()->IsHero() ? "true" : "false" );
		printf( "IsDragon : %s\n", ObjectManager::GetPlayer()->IsDragon() ? "true" : "false" );
		printf( "IsTroy : %s\n", ObjectManager::GetPlayer()->IsTroy() ? "true" : "false" );
		printf( "IsAlive : %s\n", ObjectManager::GetPlayer()->IsAlive() ? "true" : "false" );
		printf( "IsTargetable : %s\n", ObjectManager::GetPlayer()->IsTargetable() ? "true" : "false" );

		// HudManager
		printf( "\nGameCursor : %#x \n", HudManager::GetGameCursor() );
		printf( "Position : (%.0f, %.0f, %.0f) \n",
			HudManager::GetGameCursor()->Position.x,
			HudManager::GetGameCursor()->Position.y,
			HudManager::GetGameCursor()->Position.z );

		// Functions
		GameFunctions::IssueOrder( HudManager::GetGameCursor()->Position, EGameObjectOrder::MoveTo );

		Game::PrintChat( "<font color='#FFFF00'>Test Print Chat ! </font>" );
	}

	static void test2()
	{
		auto vec = Vector3( 0, 0, 0 );
	}
}
