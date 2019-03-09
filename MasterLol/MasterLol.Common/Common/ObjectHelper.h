#pragma once
#include <SDK/UnitInclude.h>
#include <SDK/ObjectManager.h>
#include <SDK/Names.h>
#include <SDK/EventManager.h>

namespace Common
{
	class ObjectList {

	private:
		static void OnUpdate();

	public:
		static std::vector<Obj_AI_Base*> mAllMinions;
		static std::vector<Obj_AI_Base*> mAllTroy;
		static std::vector<Obj_AI_Turret*> mAllTurrets;
		static std::vector<AIHeroClient*> mAllHeros;
		static std::vector<GameObject*> mAllMissiles;
		static std::vector<AttackableUnit*> mAllInhibitors;
		static std::vector<AttackableUnit*> mAllNexus;
		static AttackableUnit* mDragon;
		static AttackableUnit* mBaron;

		static void Initialize()
		{
			EventHandler<EventIndex::OnMainLoop, EventDefines::OnMainLoop>::GetInstance()->Add(ObjectList::OnUpdate);
		}
	};

	class ObjectHelper
	{
	private:

	public:
		static bool IsEnnemy(Obj_AI_Base* target, Obj_AI_Base* source = ObjectManager::GetPlayer());
		static bool IsAttackable(Obj_AI_Base*);
		static bool IsInRange(GameObject*, float distance, GameObject* source = ObjectManager::GetPlayer(), bool takeBoundingRadius = true);
		static bool IsValidTarget(Obj_AI_Base*, float distance = FLT_MAX, Obj_AI_Base* source = ObjectManager::GetPlayer());

		static bool IsSpecificAiMinion(Obj_AI_Base* unit, Names::AIMinionTypes::AIMinionTypes);
		static bool IsSpecificJungleMob(Obj_AI_Base* unit, Names::JungleMob::JungleMob);
		static bool IsMinion(Obj_AI_Base* unit);
		static bool IsJungleMob(Obj_AI_Base* unit);


		//template <typename Type>
		//static std::vector<Type*> GetAllObjectType(EUnitType type);
		//static std::vector<Obj_AI_Base*> GetAllMinions();
		//static std::vector<Obj_AI_Base*> GetAllMinions(float range, Obj_AI_Base* source);

	};

	//template<typename Type>
	//inline std::vector<Type*> ObjectHelper::GetAllObjectType(EUnitType type)
	//{
	//	GameObject** unitArray = ObjectManager::GetUnitArray()
	//	std::vector<Type*> ret;
	//	for (size_t i = 0; i < ObjectManager::GetHighestObjectId(); ++i)
	//	{
	//		if (unitArray[i]->GetType() == type)
	//			ret.push_back((Type*)unitArray[i]);
	//	}
	//	return ret;
	//}
}