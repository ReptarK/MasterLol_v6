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
	typedef bool(__cdecl* _fnIsNotWall)(Vector3*, unsigned __int16);
	static _fnIsNotWall oIsNotWall = (_fnIsNotWall)(Patchables::LolBase + fnIsNotWall);

	return !oIsNotWall(&worldPosition, 0);
}
