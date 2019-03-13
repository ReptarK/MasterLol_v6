#pragma once
#include "GameObject.h"
#include "SpellData.h"
#include "SpellInfo.h"

class MissileClientData
{
public:
	SpellInfo * GetSpellInfo()
	{
		if (this != nullptr)
		{
			return reinterpret_cast<SpellInfo*>(this);
		}

		return nullptr;
	}
};

class MissileClient
	: public GameObject
{
public:
	MAKE_GET(LaunchPos, Vector3, Offsets::MissileClient::LaunchPos);
	MAKE_GET(DestPos, Vector3, Offsets::MissileClient::DestPos);

	int GetCreatedTimeMs()
	{
		return (int)(1000 * (*reinterpret_cast<float*>(this + static_cast<int>(Offsets::MissileClient::CreatedTime))));
	}

	uint* GetSpellCasterId()
	{
		return reinterpret_cast<uint*>(this + static_cast<int>(Offsets::MissileClient::CasterId));
	}

	uint* GetTargetId()
	{
		return reinterpret_cast<uint*>(this + static_cast<int>(Offsets::MissileClient::TargetId));
	}

	SpellInfo* GetMissileSpellInfo() 
	{
		return *reinterpret_cast<SpellInfo**>(this + static_cast<int>(Offsets::MissileClient::MissileSpellInfo));
	}
};
