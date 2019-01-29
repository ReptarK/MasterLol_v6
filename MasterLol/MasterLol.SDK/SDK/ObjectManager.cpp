#include "stdafx.h"
#include "ObjectManager.h"
#include "AIHeroClient.h"
#include "Obj_AI_Turret.h"
#include "Hooks.h"
#include "EventManager.h"

uint ObjectManager::GetMaxSize()
{
	ObjectManager_struct* objectManager = reinterpret_cast<ObjectManager_struct*>(Patchables::LolBase + oObjManager);
	if (!objectManager)
		return 0;

	return objectManager->size;
}

uint ObjectManager::GetUsedIndexes()
{
	ObjectManager_struct* objectManager = reinterpret_cast<ObjectManager_struct*>(Patchables::LolBase + oObjManager);
	if (!objectManager)
		return 0;

	return objectManager->usedIndexes;
}

uint ObjectManager::GetHighestObjectId()
{
	ObjectManager_struct* objectManager = reinterpret_cast<ObjectManager_struct*>(Patchables::LolBase + oObjManager);
	if (!objectManager)
		return 0;

	return objectManager->highestObjectId;
}

uint ObjectManager::GetHighestPlayerId()
{
	ObjectManager_struct* objectManager = reinterpret_cast<ObjectManager_struct*>(Patchables::LolBase + oObjManager);
	if (!objectManager)
		return 0;

	return objectManager->highestHeroId;
}

GameObject ** ObjectManager::GetUnitArray()
{
	ObjectManager_struct* objectManager = reinterpret_cast<ObjectManager_struct*>(Patchables::LolBase + oObjManager);
	if (!objectManager)
		return nullptr;

	return objectManager->objectArray;
}

AIHeroClient* ObjectManager::GetPlayer()
{
	return *reinterpret_cast<AIHeroClient**>(Patchables::LolBase + oLocalPlayer);
}

GameObject * ObjectManager::GetUnitByNetworkId(uint networkId)
{
	__try
	{
		if (networkId != 0)
		{
			for (auto i = 0; i < 10000; i++)
			{
				auto unit = GetUnitArray()[i];
				if (unit != nullptr)
				{
					auto netId = unit->GetNetworkId();
					if (netId != nullptr)
					{
						if (*netId == networkId && *netId >= 0x3FFFFCC8)
						{
							return unit;
						}
					}
				}
			}
		}
	}
	__except (1) {}

	return nullptr;
}



std::vector<GameObject*> ObjectManager::GetType(EUnitType type)
{
	GameObject** unitArray = GetUnitArray();
	std::vector<GameObject*> ret;
	for (size_t i = 0; i < GetHighestObjectId(); ++i)
	{
		if (unitArray[i]->GetType() == type)
			ret.push_back(unitArray[i]);
	}
	return ret;
}

template<class T>
inline std::vector<T*> ObjectManager::GetType(EUnitType type)
{
	GameObject** unitArray = GetUnitArray();
	std::vector<T*> ret;
	for (size_t i = 0; i < GetHighestObjectId(); ++i)
	{
		if (unitArray[i]->GetType() == type)
			ret.push_back((T*)unitArray[i]);
	}
	return ret;
}

GameObject* ObjectManager::operator[](const uint index)
{
	return GetUnitArray()[index];
}

AIHeroClient * ObjectManager::GetHeroFromChampionEnum( EChampion::EChampion championToFind, bool isAlly)
{
	auto player = ObjectManager::GetPlayer();
	auto heros = ObjectManager::GetType<AIHeroClient>(EUnitType::Hero);
	for (auto hero : heros)
	{
		// Team Check
		if (isAlly && *hero->GetTeam() != *player->GetTeam())
			continue;
		else if (!isAlly && *hero->GetTeam() == *player->GetTeam())
			continue;

		if (hero->GetHero() == championToFind)
			return hero;
	}
	return nullptr;
}

template<class ToType, class AType, class BType>
inline std::vector<ToType> ObjectManager::Merge(std::vector<AType>& A, std::vector<BType>& B)
{
	std::vector<ToType> mergedList;
	mergedList.reserve(A.size() + B.size()); // preallocate memory
	mergedList.insert(mergedList.end(), A.begin(), A.end());
	mergedList.insert(mergedList.end(), B.begin(), B.end());
	return mergedList;
}

std::vector<Obj_AI_Base*> ObjectManager::ConvertToAIBase(std::vector<AIHeroClient*> vec)
{
	std::vector<Obj_AI_Base*> retVec;
	retVec.reserve(vec.size());
	for (auto object : vec)
	{
		retVec.push_back((Obj_AI_Base*)object);
	}
	return retVec;
}

std::vector<AIHeroClient*> ObjectManager::ConvertToAIHero(std::vector<Obj_AI_Base*> vec)
{
	std::vector<AIHeroClient*> retVec;
	retVec.reserve(vec.size());
	for (auto object : vec)
	{
		retVec.push_back((AIHeroClient*)object);
	}
	return retVec;
}
