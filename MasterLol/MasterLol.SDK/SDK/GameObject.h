#pragma once
#include "stdafx.h"
#include "Offsets.h"
#include "math/Vector.hpp"
#include "StaticEnums.h"
#include "Macros.h"
#include "GameObjectVTable.h"

struct BBox
{
	float MinimumX;
	float MinimumY;
	float MinimumZ;
	float MaximumX;
	float MaximumY;
	float MaximumZ;
};

class GameObject
{
public:
	GameObjectVTable * GetVirtual();

	MAKE_GET(Index, short, Offsets::GameObject::Index);
	MAKE_GET(Team, GameObjectTeam, Offsets::GameObject::Team);
	MAKE_GET(NetworkId, uint, Offsets::GameObject::NetworkId);
	MAKE_GET(IsVisible, bool, Offsets::GameObject::VisibleOnScreen);

	float GetBoundingRadius();

	bool IsHero();
	bool IsMissile();
	bool IsMinion();
	bool IsTurret();
	bool IsInhibitor();
	bool IsTroyEnt();
	bool IsNexus();


	Vector3 GetPos();
	std::string GetName();
};
