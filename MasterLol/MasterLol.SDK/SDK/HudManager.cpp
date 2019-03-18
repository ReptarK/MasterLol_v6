#include "stdafx.h"
#include "HudManager.h"

GameCursor * HudManager::GetGameCursor()
{
	DWORD hudInstance = *reinterpret_cast< DWORD* >( Patchables::LolBase + oHudInstance );

	return *reinterpret_cast< GameCursor** >( hudInstance + ( int )Offsets::HudInstance::GameCursor );
}

GameObject * HudManager::GetUnderMouseObject()
{
	__try
	{
		return *reinterpret_cast< GameObject** >( Patchables::LolBase + oUnderMouseObj );
	}
	__except ( 1 ) { return nullptr; }
}

bool HudManager::IsWall(Vector3 worldPosition)
{
	typedef bool(__cdecl* fnIsNotWall)(Vector3*, unsigned __int16);
	static fnIsNotWall oIsNotWall = (fnIsNotWall)(Patchables::LolBase + fnIsWall);

	return !oIsNotWall(&worldPosition, 0);
}
