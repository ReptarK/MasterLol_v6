#pragma once
#include <vector>
#include <d3d9.h>
#include <memory>

#include <SDK/singleton.hpp>
#include "IComponent.h"

class ComponentsManager {

public:
	static std::vector<std::unique_ptr<IComponent>> mComponents;

	static void Initialize();
	static void Shutdown();

	static void OnUpdate();
	static void OnEndScene(IDirect3DDevice9*);

	template<typename T>
	static void AddComponent();
};

template<typename T>
inline void ComponentsManager::AddComponent()
{
	ComponentsManager::mComponents.push_back(std::make_unique<T>());
}
