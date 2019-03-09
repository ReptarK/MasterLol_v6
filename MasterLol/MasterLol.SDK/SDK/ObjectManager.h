#pragma once
#include "stdafx.h"
#include "singleton.hpp"
#include "Macros.h"
#include "StaticEnums.h"

class AIHeroClient;
class GameObject;
class Obj_AI_Base;

class ObjectManager
{
	struct ObjectManager_struct
	{
		char pad_0000[8];
		GameObject** objectArray;	// 0x08
		uint size;					// 0x0C
		uint usedIndexes;			// 0x10
		uint highestObjectId;		// 0x14
		uint highestHeroId;			// 0x18
	};

	ObjectManager() {}
	~ObjectManager() {}

public:
	static uint GetMaxSize();
	static uint GetUsedIndexes();
	static uint GetHighestObjectId();
	static uint GetHighestPlayerId();

	static GameObject** GetUnitArray();
	static AIHeroClient* GetPlayer();

	static GameObject* GetUnitByNetworkId(uint networkId);


	static std::vector<GameObject*> GetType(EUnitType type);
	template<class T>
	static std::vector<T*> GetType(EUnitType type);

	GameObject* operator[] (const uint index);

	static AIHeroClient* GetHeroFromChampionEnum( EChampion::EChampion, bool isAlly = false);

#pragma region LIST HELPERS
	template<class ToType, class AType, class BType>
	static std::vector<ToType> Merge(std::vector<AType>& A, std::vector<BType>& B);

	static std::vector<Obj_AI_Base*> ConvertToAIBase(std::vector<AIHeroClient*> vec);
	static std::vector<AIHeroClient*> ConvertToAIHero(std::vector<Obj_AI_Base*> vec);
#pragma endregion
};

class ObjectIterator {
private:
	int mCurrIndex;
	GameObject** mUnits;

public:
	ObjectIterator() {
		mUnits = ObjectManager::GetUnitArray();
		mCurrIndex = -1;
	}

	bool End()
	{
		return mCurrIndex + 1 > ObjectManager::GetHighestObjectId();
	}

	GameObject* Next()
	{
		return mUnits[++mCurrIndex];
	}
};


