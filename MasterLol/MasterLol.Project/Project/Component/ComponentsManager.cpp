#include "ComponentsManager.h"

#include <SDK/EventManager.h>

std::vector<std::unique_ptr<IComponent>> ComponentsManager::mComponents;

void ComponentsManager::Initialize()
{
	ComponentsManager::mComponents = std::vector<std::unique_ptr<IComponent>>();

	EventHandler<EventIndex::OnDrawingEndScene, EventDefines::OnDrawingEndScene, IDirect3DDevice9*>::GetInstance()->Add(ComponentsManager::OnEndScene);

	EventHandler<EventIndex::OnUpdate, EventDefines::OnMainLoop>::GetInstance()->Add(ComponentsManager::OnUpdate);

	EventHandler<EventIndex::OnMissileProcessSpell, EventDefines::OnMissileProcessSpell,
		MissileClient*, GameObject*>::GetInstance()->Add(ComponentsManager::OnMissileProcessSpell);
}

void ComponentsManager::Shutdown()
{
	EventHandler<EventIndex::OnDrawingEndScene, EventDefines::OnDrawingEndScene, IDirect3DDevice9*>::GetInstance()->Remove(ComponentsManager::OnEndScene);

	EventHandler<EventIndex::OnUpdate, EventDefines::OnMainLoop>::GetInstance()->Remove(ComponentsManager::OnUpdate);

	EventHandler<EventIndex::OnMissileProcessSpell, EventDefines::OnMissileProcessSpell,
		MissileClient*, GameObject*>::GetInstance()->Remove(ComponentsManager::OnMissileProcessSpell);

	ComponentsManager::mComponents.clear();
}

void ComponentsManager::OnUpdate()
{
	for (auto it = ComponentsManager::mComponents.begin(); it != ComponentsManager::mComponents.end(); it++) {
		(*it)->OnUpdate();
	}
}

void ComponentsManager::OnEndScene(IDirect3DDevice9 *)
{
	for (auto it = ComponentsManager::mComponents.begin(); it != ComponentsManager::mComponents.end(); it++) {
		(*it)->OnEndScene();
	}
}

void ComponentsManager::OnMissileProcessSpell(MissileClient * missile, Obj_AI_Base * caster)
{
	for (auto it = ComponentsManager::mComponents.begin(); it != ComponentsManager::mComponents.end(); it++) {
		(*it)->OnMissileProcessSpell(missile, caster);
	}
}
