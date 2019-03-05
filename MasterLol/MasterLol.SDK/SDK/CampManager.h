#pragma once

#include "stdafx.h"
#include "GameObject.h"

class CampManagerClient;

class CampManager {
public:

	static CampManagerClient* GetCampManagerClient() {
		return *(CampManagerClient**)(Patchables::LolBase + oCampManagerClient);
	}

	static GameObject* GetCampObjectFromId(BYTE campId) {
		typedef GameObject*(__thiscall* _fnFindCamp)(CampManagerClient* campManagerClient, BYTE campId);
		_fnFindCamp findCamp = (_fnFindCamp)(Patchables::LolBase + fnFindCamp);
		return findCamp(CampManager::GetCampManagerClient(), campId);
	}

	static float GetTimerExpiry(BYTE campId) {
		typedef float(__thiscall* _fnGetTimerExpiry)(GameObject* camp);
		_fnGetTimerExpiry getTimerExpiry = (_fnGetTimerExpiry)(Patchables::LolBase + fnGetTimerExpiry);
		return getTimerExpiry(CampManager::GetCampObjectFromId(campId));
	}
};
