#pragma once
#include "stdafx.h"
#include "Offsets.h"
#include "math/Vector.hpp"
#include "StaticEnums.h"
#include "Macros.h"
#include "GameObjectVTable.h"

class ObjectType
{
public:
	char pad_0000[0x1C]; //0x0000
	LolString Name; //0x001C
};

class GameObject
{
public:
	GameObjectVTable * GetVirtual();

	MAKE_GET( Index, short, Offsets::GameObject::Index );
	MAKE_GET( Team, EGameObjectTeam, Offsets::GameObject::Team );
	MAKE_GET( NetworkId, uint, Offsets::GameObject::NetworkId );
	MAKE_GET( IsVisible, bool, Offsets::GameObject::IsVisible );
	MAKE_GET(SourceIndex, short, Offsets::GameObject::SourceIndex);

	float GetBoundingRadius();

	// Types
	ObjectType * GetObjectTypeName();
	EUnitType GetUnitId();
	bool IsUnitId(EUnitType id );

	bool IsHero();
	bool IsMissile();
	bool IsMinion();
	bool IsTurret();
	bool IsInhibitor();
	bool IsTroy();
	bool IsNexus();
	bool IsDragon();
	bool IsBaron();

	EUnitType GetType();

	Vector3 GetPos();
	bool GetHpBarPosition(Vector3*);

	std::string GetName();
};
