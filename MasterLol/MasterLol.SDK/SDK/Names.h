#pragma once
#include <algorithm>
#include <string> 
#include "EnumMacro.h"
#include "GameObject.h"

namespace Names
{
	DECLARE_ENUM(InvalidTargets,
		JarvanIVStandard,
		ZyraSeed
	)

	DECLARE_ENUM(AIMinionTypes,
		Minion,
		Plant,
		SightWard,
		Jungle
	)

	DECLARE_ENUM(JungleMob,
		Gromp,
		Krug, MiniKrug,
		Crab,
		Murkwolf, MurkwolfMini,
		Razorbeak, RazorbeakMini,
		SRU_Red, SRU_Blue,
		Baron,
		Dragon
	)

	static bool IsName( GameObject* object, std::string name )
	{
		std::transform( name.begin(), name.end(), name.begin(), ::tolower );
		std::string objectLowerName = object->GetName();
		std::transform( objectLowerName.begin(), objectLowerName.end(), objectLowerName.begin(), ::tolower );

		return objectLowerName == name;
	}

	static bool ContainsName( GameObject* object, std::string name )
	{
		std::transform( name.begin(), name.end(), name.begin(), ::tolower );
		std::string objectLowerName = object->GetName();
		std::transform( objectLowerName.begin(), objectLowerName.end(), objectLowerName.begin(), ::tolower );

		return objectLowerName.find( name ) != std::string::npos;
	}

	static bool NameBeginWith(GameObject* object, std::string name)
	{
		std::string objectName = object->GetName();
		for (int i = 0; i < name.length(); ++i) {
			if (objectName.at(i) != name.at(i))
				return false;
		}

		return true;
	}
}

