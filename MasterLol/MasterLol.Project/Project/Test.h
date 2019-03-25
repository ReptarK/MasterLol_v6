#pragma once
#include <SDK/Game.h>
#include <SDK/colors_define.h>
#include <SDK/ObjectManager.h>
#include <SDK/AIHeroClient.h>
#include <SDK/colors_define.h>
#include <SDK/HudManager.h>
#include <SDK/Hooks.h>

#include <Common/GameFunctions.h>
#include <Common/GameEvent.h>

namespace TEST
{
	static void test1()
	{
		// LocalPlayer
		printf("LocalPlayer : %#x \n", ObjectManager::GetPlayer());
		printf("\t AI Manager : %#x \n", ObjectManager::GetPlayer()->GetNavigation());
		printf("\t Name : %s \n", ObjectManager::GetPlayer()->GetName().c_str());
		printf("\t Position : (%.0f, %.0f, %.0f) \n",
			ObjectManager::GetPlayer()->GetPos().x,
			ObjectManager::GetPlayer()->GetPos().y,
			ObjectManager::GetPlayer()->GetPos().z);
		printf("\t BoundingRadius : %.0f \n", ObjectManager::GetPlayer()->GetBoundingRadius());
		printf("\t GetAttackCastDelay : %.4f \n", ObjectManager::GetPlayer()->GetAttackCastDelay());
		printf("\t GetAttackDelay : %.4f \n", ObjectManager::GetPlayer()->GetAttackDelay());

		printf("IsAlive : %s\n", ObjectManager::GetPlayer()->IsAlive() ? "true" : "false");
		printf("IsTargetable : %s\n", ObjectManager::GetPlayer()->IsTargetable() ? "true" : "false");


		printf("IsHero : %s\n", ObjectManager::GetPlayer()->IsHero() ? "true" : "false");
		printf("IsTroy : %s\n", ObjectManager::GetPlayer()->IsTroy() ? "true" : "false");
		printf("IsNexus : %s\n", ObjectManager::GetPlayer()->IsNexus() ? "true" : "false");
		printf("IsMinion : %s\n", ObjectManager::GetPlayer()->IsMinion() ? "true" : "false");
		printf("IsInhibitor : %s\n", ObjectManager::GetPlayer()->IsInhibitor() ? "true" : "false");
		printf("IsMissile : %s\n", ObjectManager::GetPlayer()->IsMissile() ? "true" : "false");
		printf("IsTurret : %s\n", ObjectManager::GetPlayer()->IsTurret() ? "true" : "false");
		printf("IsDragon : %s\n", ObjectManager::GetPlayer()->IsDragon() ? "true" : "false");



		// HudManager
		printf("\nGameCursor : %#x \n", HudManager::GetGameCursor());
		printf("Position : (%.0f, %.0f, %.0f) \n",
			HudManager::GetGameCursor()->Position.x,
			HudManager::GetGameCursor()->Position.y,
			HudManager::GetGameCursor()->Position.z);

		// Functions
		//GameFunctions::IssueOrder(HudManager::GetGameCursor()->Position, EGameObjectOrder::MoveTo);

		Game::PrintChat("mAllHeros COUNT : %d", BLUE(), Common::ObjectList::mAllHeros.size());
		Game::PrintChat("mAllMinions COUNT : %d", BLUE(), Common::ObjectList::mAllMinions.size());
		//Game::PrintChat("mAllTroy COUNT : %d", BLUE(), Common::ObjectList::mAllTroy.size());
		//Game::PrintChat("mAllTurrets COUNT : %d", BLUE(), Common::ObjectList::mAllTurrets.size());
		//Game::PrintChat("mAllMissiles COUNT : %d", BLUE(), Common::ObjectList::mAllMissiles.size());
		//Game::PrintChat("mAllInhibitors COUNT : %d", BLUE(), Common::ObjectList::mAllInhibitors.size());
		//Game::PrintChat("mAllNexus COUNT : %d", BLUE(), Common::ObjectList::mAllNexus.size());
		Game::PrintChat("IsWall On Mouse : %s\n", GREEN(), HudManager::IsWall(HudManager::GetGameCursor()->Position) ? "true" : "false");

	}


	static void test2()
	{
		Obj_AI_Base* currentObject = (Obj_AI_Base*)HudManager::GetUnderMouseObject();
		if (currentObject) 
		{
			printf("Object ID : %x \n", currentObject->GetUnitId());
			printf("\t Navigation : %#x \n", currentObject->GetNavigation());
			printf("\t Name : %s \n", currentObject->GetName().c_str());
			printf("\t Position : (%.0f, %.0f, %.0f) \n",
				currentObject->GetPos().x,
				currentObject->GetPos().y,
				currentObject->GetPos().z);
			printf("\t BoundingRadius : %.0f \n", currentObject->GetBoundingRadius());

			printf("IsAlive : %s\n", currentObject->IsAlive() ? "true" : "false");
			printf("IsTargetable : %s\n", currentObject->IsTargetable() ? "true" : "false");


			printf("IsHero : %s\n", currentObject->IsHero() ? "true" : "false");
			printf("IsTroy : %s\n", currentObject->IsTroy() ? "true" : "false");
			printf("IsNexus : %s\n", currentObject->IsNexus() ? "true" : "false");
			printf("IsMinion : %s\n", currentObject->IsMinion() ? "true" : "false");
			printf("IsInhibitor : %s\n", currentObject->IsInhibitor() ? "true" : "false");
			printf("IsMissile : %s\n", currentObject->IsMissile() ? "true" : "false");
			printf("IsTurret : %s\n", currentObject->IsTurret() ? "true" : "false");
			printf("IsDragon : %s\n", currentObject->IsDragon() ? "true" : "false");
		}
	}

	static void test3()
	{
		auto localPlayer = ObjectManager::GetPlayer();
		if (!localPlayer) return;

		auto buffManager = *localPlayer->GetBuffManager();
		// LIST ALL BUFF
		int size = ((DWORD)buffManager.mEnd - (DWORD)buffManager.mBuffArray) / 0x4;
		printf("mBuffArray : %#x \n", buffManager.mBuffArray);
		printf("mEnd : %#x \n", buffManager.mEnd);
		printf("size : %d \n", size);
		for (int i = 0; i < size; ++i)
		{
			BuffNode* currBuff = buffManager.mBuffArray[i];
			BuffInstance* currBuffInstance = currBuff->mBuffInstance;
			if ((DWORD)currBuffInstance < 0x10000000)
				continue;

			printf("currBuff : %#x \n", currBuff);
			printf("currBuffInstance : %#x \n", currBuffInstance);
			printf("\t Name : %s \n", currBuffInstance->mName);
			printf("\t Active Time : %.0f \n", currBuff->mEndTime - currBuff->mStartTime);
		}
	}

	static void test4() 
	{
		std::cout << "Enter Buff Name : ";
		std::string buffName;
		std::cin >> buffName;

		auto buffManager = *ObjectManager::GetPlayer()->GetBuffManager();
		auto buff = buffManager.GetBuffFromName(buffName.c_str());
		printf("currBuff : %#x \n", buff);
		printf("currBuffInstance : %#x \n", buff);
		try {
			printf("\t Name : %s \n", buff->mBuffInstance->mName);
			printf("\t Active Time : %.0f \n", buff->mEndTime - buff->mStartTime);
			printf("\t\t boolFn1 : %s \n", buff->mBuffInstance->GetVirtual()->boolFn1() ? "true" : "false");
			printf("\t\t boolFn2 : %s \n", buff->mBuffInstance->GetVirtual()->boolFn2() ? "true" : "false");
			printf("\t\t charFn1 : %s \n", buff->mBuffInstance->GetVirtual()->charFn1() ? "true" : "false");
			printf("\t\t intFn1 : %#x \n", buff->mBuffInstance->GetVirtual()->intFn1());
			printf("\t\t intFn3 : %#x \n", buff->mBuffInstance->GetVirtual()->intFn3());
			printf("\t\t sigIntFn1 : %#x \n", buff->mBuffInstance->GetVirtual()->sigIntFn1());
		}
		catch (const std::exception& e) { printf(e.what()); }
	}

	//MAKE_HOOK<convention_type::thiscall_r, void, void*, int> IssueOrderHook;
	//void __fastcall OnIssueOrder(void* unk_ptr, void *EDX, int unk_int)
	//{
	//	std::printf("OnIssueOrder(%#x, %d)", unk_ptr, unk_int);
	//	IssueOrderHook.CallOriginal(unk_ptr, unk_int);
	//}

	static void test5()
	{
		Game::PrintChat("ActiveProcessSpell : %d", GREEN(), Common::OnProcessSpell::mActiveProcessSpell.size());
		//IssueOrderHook.Apply(Patchables::LolBase + 0x208A10, OnIssueOrder);
	}

	static void testNavigation() 
	{
		AIHeroClient* player = ObjectManager::GetPlayer();
		Navigation* navigation = player->GetNavigation();
		PathManager pathManager = navigation->mPathManager;
		printf("Log Navigation : \n");
		printf("\t Size : %d \n", pathManager.GetSize());
		printf("\t End : %#x \n", pathManager.mEnd);
		printf("\t Begin : %#x \n", pathManager.mPath);

		int size = pathManager.GetSize();
		for (int i = 0; i < size; ++i)
		{
			Vector3 currWaypoint = pathManager.mPath[i];
			printf("\t WayPoint : ( %.0f, %.0f, %.0f )\n", currWaypoint.x, currWaypoint.y, currWaypoint.z);
		}
	}
}
