#pragma once

#include "VisualComponent.h"
#include "Debug.component/DebugComponent.h"

class Components
{
public:
	static std::vector<IComponent> mComponents;

	static void Initialize()
	{
		VisualComponent::Initialize();
		DebugComponent::Initialize();
	}
};
