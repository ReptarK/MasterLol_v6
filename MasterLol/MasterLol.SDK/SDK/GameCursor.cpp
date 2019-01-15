#include "stdafx.h"
#include "GameCursor.h"

Vector3 GameCursor::GetPos()
{
	DWORD ptr = *reinterpret_cast<DWORD*>(Patchables::LolBase + oHudInstance);
	if (!ptr)
	{
		return Vector3(0, 0, 0);
	}

	auto vec = reinterpret_cast<Vector3*>(ptr + static_cast<int>(Offsets::GameCursor::Position));
	if (vec == nullptr)
	{
		return Vector3(0, 0, 0);
	}

	return Vector3(vec->x, vec->y, vec->z);
}

GameObject * GameCursor::GetUnderMouseObject()
{
	return nullptr;
	//__try
	//{
	//	return *reinterpret_cast<GameObject**>(Patchables::LolBase + oUnderMouseObject);
	//}
	//__except (1) { return nullptr; }
}
