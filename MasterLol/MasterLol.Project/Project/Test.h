#pragma once
#include <SDK/Game.h>
#include <SDK/colors_define.h>
#include <SDK/ObjectManager.h>
#include <SDK/AIHeroClient.h>
#include <SDK/colors_define.h>
#include <Common/GameFunctions.h>
#include <SDK/HudManager.h>

#include <SDK/Hooks.h>

namespace TEST
{
	static void test1()
	{
		// LocalPlayer
		printf( "LocalPlayer : %#x \n", ObjectManager::GetPlayer() );
		printf( "\t AI Manager : %#x \n", ObjectManager::GetPlayer()->GetNavigation() );
		printf( "\t Name : %s \n", ObjectManager::GetPlayer()->GetName().c_str() );
		printf( "\t Position : (%.0f, %.0f, %.0f) \n",
			ObjectManager::GetPlayer()->GetPos().x,
			ObjectManager::GetPlayer()->GetPos().y,
			ObjectManager::GetPlayer()->GetPos().z );
		printf( "\t BoundingRadius : %.0f \n", ObjectManager::GetPlayer()->GetBoundingRadius() );

		printf( "IsAlive : %s\n", ObjectManager::GetPlayer()->IsAlive() ? "true" : "false" );
		printf( "IsTargetable : %s\n", ObjectManager::GetPlayer()->IsTargetable() ? "true" : "false" );


		printf( "IsHero : %s\n", ObjectManager::GetPlayer()->IsHero() ? "true" : "false" );
		printf( "IsTroy : %s\n", ObjectManager::GetPlayer()->IsTroy() ? "true" : "false" );
		printf( "IsMinion : %s\n", ObjectManager::GetPlayer()->IsMinion() ? "true" : "false" );
		printf( "IsNexus : %s\n", ObjectManager::GetPlayer()->IsNexus() ? "true" : "false" );
		printf( "IsInhibitor : %s\n", ObjectManager::GetPlayer()->IsInhibitor() ? "true" : "false" );
		printf( "IsMissile : %s\n", ObjectManager::GetPlayer()->IsMissile() ? "true" : "false" );
		printf( "IsTurret : %s\n", ObjectManager::GetPlayer()->IsTurret() ? "true" : "false" );
		printf( "IsDragon : %s\n", ObjectManager::GetPlayer()->IsDragon() ? "true" : "false" );



		// HudManager
		printf( "\nGameCursor : %#x \n", HudManager::GetGameCursor() );
		printf( "Position : (%.0f, %.0f, %.0f) \n",
			HudManager::GetGameCursor()->Position.x,
			HudManager::GetGameCursor()->Position.y,
			HudManager::GetGameCursor()->Position.z );

		// Functions
		GameFunctions::IssueOrder( HudManager::GetGameCursor()->Position, EGameObjectOrder::MoveTo );

		Game::PrintChat( "Test 1", BLUE() );
	}


	static void test2()
	{
		GameObject* currentObject = HudManager::GetUnderMouseObject();
		if ( currentObject )
			printf( "Object ID : %x \n", currentObject->GetUnitId() );
	}

	static void test3()
	{
		Obj_AI_Base::ApplyHooks();
	}


}
