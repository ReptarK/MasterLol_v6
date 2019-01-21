#pragma once
#include "stdafx.h"
#include "Offsets.h"
#include "math/Vector.hpp"
#include "StaticEnums.h"
#include "Macros.h"
#include "GameObjectVTable.h"

class GameObject
{
public:
	GameObjectVTable * GetVirtual();

	MAKE_GET( Index, short, Offsets::GameObject::Index );
	MAKE_GET( Team, EGameObjectTeam, Offsets::GameObject::Team );
	MAKE_GET( NetworkId, uint, Offsets::GameObject::NetworkId );
	MAKE_GET( IsVisible, bool, Offsets::GameObject::VisibleOnScreen );

	float GetBoundingRadius();

	// Types
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
	std::string GetName();
};
