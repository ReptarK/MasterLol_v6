#pragma once
#include "stdafx.h"
#include "singleton.hpp"
#include "Macros.h"
#include "StaticEnums.h"

class AIHeroClient;
class GameObject;
class Obj_AI_Base;

class ObjectManager
	:public Singleton<ObjectManager>
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
	friend class Singleton<ObjectManager>;

	ObjectManager() {}
	~ObjectManager() {}

public:
	uint GetMaxSize();
	uint GetUsedIndexes();
	uint GetHighestObjectId();
	uint GetHighestPlayerId();

	GameObject** GetUnitArray();
	AIHeroClient* GetPlayer();

	GameObject* GetUnitByNetworkId(uint networkId);


	std::vector<GameObject*> GetType(UnitType type);
	template<class T>
	std::vector<T*> GetType(UnitType type);

	GameObject* operator[] (const uint index);

	static AIHeroClient* GetHeroFromChampionEnum(Champion::Champion, bool isAlly = false);

#pragma region LIST HELPERS
	template<class ToType, class AType, class BType>
	static std::vector<ToType> Merge(std::vector<AType>& A, std::vector<BType>& B);

	static std::vector<Obj_AI_Base*> ConvertToAIBase(std::vector<AIHeroClient*> vec);
	static std::vector<AIHeroClient*> ConvertToAIHero(std::vector<Obj_AI_Base*> vec);
#pragma endregion
};


