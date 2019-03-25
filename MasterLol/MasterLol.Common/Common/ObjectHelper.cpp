#include "ObjectHelper.h"

namespace Common
{
#pragma region Single Unit Helper

	bool ObjectHelper::IsEnnemy(Obj_AI_Base * target, Obj_AI_Base * source)
	{
		return *target->GetTeam() != *source->GetTeam();
	}

	bool ObjectHelper::IsAttackable(Obj_AI_Base * unit)
	{
		return unit->IsAlive() && unit->IsTargetable();
	}

	bool ObjectHelper::IsInRange(GameObject * object, float distance, GameObject* source, bool takeBoundingRadius)
	{
		float rangeSqr;
		if (takeBoundingRadius)
		{
			auto objectBoundingBox = object->GetBoundingRadius();
			auto sourceBoundingBox = source->GetBoundingRadius();
			auto boundingBoxTotalDistanceSqr = objectBoundingBox * objectBoundingBox + sourceBoundingBox * sourceBoundingBox;
			float realRange = distance + objectBoundingBox + sourceBoundingBox;
			rangeSqr = realRange * realRange;
			return source->GetPos().DistToSqr(object->GetPos()) <= rangeSqr;
		}
		else {
			rangeSqr = distance * distance;
			return source->GetPos().DistToSqr(object->GetPos()) < rangeSqr;
		}
	}

	bool ObjectHelper::IsValidTarget(Obj_AI_Base * target, float distance, Obj_AI_Base * source)
	{
		return IsEnnemy(target, source) && IsAttackable(target) && IsInRange(target, distance, source, true);
	}

	bool ObjectHelper::IsSpecificAiMinion(Obj_AI_Base * unit, Names::AIMinionTypes::AIMinionTypes aiMinionType)
	{
		return Names::ContainsName(unit, Names::AIMinionTypes::ToString(aiMinionType));
	}

	bool ObjectHelper::IsSpecificJungleMob(Obj_AI_Base * unit, Names::JungleMob::JungleMob jungleMob)
	{
		return Names::ContainsName(unit, Names::JungleMob::ToString(jungleMob));
	}

	bool ObjectHelper::IsMinion(Obj_AI_Base* unit)
	{
		return IsSpecificAiMinion(unit, Names::AIMinionTypes::Minion);
	}

	bool ObjectHelper::IsJungleMob(Obj_AI_Base* unit)
	{
		return IsSpecificAiMinion(unit, Names::AIMinionTypes::Jungle);
	}

	GameObject * ObjectHelper::GetSourceObject(GameObject * childObject)
	{
		short sourceIndex = *childObject->GetSourceIndex();
		if (sourceIndex > ObjectManager::GetHighestObjectId())
			return nullptr;

		return ObjectManager::GetUnitArray()[sourceIndex];
	}

	Obj_AI_Base * ObjectHelper::GetLowestHp(std::vector<Obj_AI_Base*> unitList)
	{
		float lowHp = FLT_MAX;
		Obj_AI_Base* result = nullptr;
		for (auto unit : unitList)
		{
			if (*unit->GetHealth() < lowHp) {
				lowHp = *unit->GetHealth();
				result = unit;
			}
		}

		return result;
	}

#pragma endregion

	std::vector<Obj_AI_Base*> ObjectList::mAllMinions;
	std::vector<Obj_AI_Base*> ObjectList::mAllTroy;
	std::vector<Obj_AI_Turret*> ObjectList::mAllTurrets;
	std::vector<AIHeroClient*> ObjectList::mAllHeros;
	std::vector<MissileClient*> ObjectList::mAllMissiles;
	std::vector<AttackableUnit*> ObjectList::mAllInhibitors;
	std::vector<AttackableUnit*> ObjectList::mAllNexus;
	Obj_AI_Base* ObjectList::mDragon;
	Obj_AI_Base* ObjectList::mBaron;

	void ObjectList::OnUpdate()
	{
		std::vector<Obj_AI_Base*> tmpAllMinions = std::vector<Obj_AI_Base*>();
		std::vector<Obj_AI_Base*> tmpAllTroy = std::vector<Obj_AI_Base*>();
		std::vector<Obj_AI_Turret*> tmpAllTurrets = std::vector<Obj_AI_Turret*>();
		std::vector<AIHeroClient*> tmpAllHeros = std::vector<AIHeroClient*>();
		std::vector<MissileClient*> tmpAllMissiles = std::vector<MissileClient*>();
		std::vector<AttackableUnit*> tmpAllInhibitors = std::vector<AttackableUnit*>();
		std::vector<AttackableUnit*> tmpAllNexus = std::vector<AttackableUnit*>();

		ObjectIterator it = ObjectIterator();
		while (!it.End())
		{
			GameObject* currObject = it.Next();
			if (!currObject)continue;

			switch (currObject->GetType())
			{
			case EUnitType::Unknown  : continue;

			case EUnitType::Minion   : tmpAllMinions.push_back((Obj_AI_Base*)currObject);		break;
			case EUnitType::Hero     : tmpAllHeros.push_back((AIHeroClient*)currObject);		break;
			case EUnitType::Missile  : tmpAllMissiles.push_back((MissileClient*)currObject);	break;
			case EUnitType::Troy     : tmpAllTroy.push_back((Obj_AI_Base*)currObject);			break;
			case EUnitType::Turret   : tmpAllTurrets.push_back((Obj_AI_Turret*)currObject);		break;
			case EUnitType::Inhibitor: tmpAllInhibitors.push_back((AttackableUnit*)currObject); break;
			case EUnitType::Nexus    : tmpAllNexus.push_back((AttackableUnit*)currObject);		break;

			case EUnitType::Dragon	 : ObjectList::mDragon = (Obj_AI_Base*)currObject;
			case EUnitType::Baron	 : ObjectList::mBaron = (Obj_AI_Base*)currObject;

			default: continue;
			}
		}

		ObjectList::mAllMinions = tmpAllMinions;
		ObjectList::mAllHeros = tmpAllHeros;
		ObjectList::mAllTroy = tmpAllTroy;
		ObjectList::mAllMissiles = tmpAllMissiles;
		ObjectList::mAllTurrets = tmpAllTurrets;
		ObjectList::mAllInhibitors = mAllInhibitors;
		ObjectList::mAllNexus = tmpAllNexus;

	}
}