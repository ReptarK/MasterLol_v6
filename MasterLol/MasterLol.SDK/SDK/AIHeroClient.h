#pragma once
#include "Obj_AI_Base.h"
#include <map>

class AIHeroClient
	: public Obj_AI_Base
{
public:

	MAKE_GET(Level, __int32, Offsets::AIHeroClient::Level);

	EChampion::EChampion GetHero();
	const static std::map<std::string, EChampion::EChampion> ChampionMap;
};
