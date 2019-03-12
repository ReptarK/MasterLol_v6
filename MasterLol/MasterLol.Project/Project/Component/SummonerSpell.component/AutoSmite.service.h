#pragma once
#include "../IGameService.h"
#include <Common/SummonerSpells.h>

class AutoSmiteService : public IGameService {

public:
	AutoSmiteService() : IGameService()
	{
		// M KEY
		InputSys::Get().RegisterHotkey(0x4D, [] {
			Option::Get().enable_auto_smite = !Option::Get().enable_auto_smite;
		});
	}

	virtual void OnUpdate();
	virtual void OnEndScene();
};

