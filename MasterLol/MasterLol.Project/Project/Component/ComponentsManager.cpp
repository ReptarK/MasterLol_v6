#include "ComponentsManager.h"
#include <SDK/EventManager.h>

std::vector<std::unique_ptr<IComponent>> ComponentsManager::mComponents;

void ComponentsManager::Initialize()
{
	ComponentsManager::mComponents = std::vector<std::unique_ptr<IComponent>>();

	EventHandler<EventIndex::OnDrawingEndScene, EventDefines::OnDrawingEndScene, IDirect3DDevice9*>::GetInstance()->Add(ComponentsManager::OnEndScene);
	EventHandler<EventIndex::OnMainLoop, EventDefines::OnMainLoop>::GetInstance()->Add(ComponentsManager::OnUpdate);
}

void ComponentsManager::Shutdown()
{
	EventHandler<EventIndex::OnDrawingEndScene, EventDefines::OnDrawingEndScene, IDirect3DDevice9*>::GetInstance()->Remove(ComponentsManager::OnEndScene);
	EventHandler<EventIndex::OnMainLoop, EventDefines::OnMainLoop>::GetInstance()->Remove(ComponentsManager::OnUpdate);

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
