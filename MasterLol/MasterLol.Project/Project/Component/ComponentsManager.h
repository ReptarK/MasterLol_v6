#pragma once
#include <vector>
#include <d3d9.h>
#include <memory>

#include <SDK/singleton.hpp>
#include <SDK/MissileClient.h>
#include <SDK/Obj_AI_Base.h>

#include "IComponent.h"

class ComponentsManager {

public:
	static std::vector<std::unique_ptr<IComponent>> mComponents;

	static void Initialize();
	static void Shutdown();

	// GameEvents
	static void OnUpdate();
	static void OnEndScene(IDirect3DDevice9*);
	static void OnCreateMissile(MissileClient* missile, Obj_AI_Base* caster);
	static void OnProcessSpell(SpellCastInfo* spell, Obj_AI_Base* caster);

	template<typename T>
	static void AddComponent();
};

template<typename T>
inline void ComponentsManager::AddComponent()
{
	ComponentsManager::mComponents.push_back(std::make_unique<T>());
}
