#include "stdafx.h"
#include "GameObject.h"
#include "GameObjectVTable.h"

GameObjectVTable * GameObject::GetVirtual()
{
	return reinterpret_cast<GameObjectVTable*>(this);
}

template< typename Function > Function CallVirtual(PVOID Base, DWORD Index)
{
	PDWORD* VTablePointer = (PDWORD*)Base;
	PDWORD VTableFunctionBase = *VTablePointer;
	DWORD dwAddress = VTableFunctionBase[Index];

	return (Function)(dwAddress);
}

float GameObject::GetBoundingRadius()
{
	__try
	{
		return this->GetVirtual()->BoundingRadius();

	}
	__except (1) { return 0; }
}

bool GameObject::IsHero()
{
	typedef bool(__cdecl* _fnIsHero)(GameObject* pObj);
	static _fnIsHero oIsHero = (_fnIsHero)(Patchables::LolBase + fnIsHero);

	return oIsHero(this);
}

bool GameObject::IsMissile()
{
	typedef bool(__cdecl* _fnIsMissile)(GameObject* pObj);
	static _fnIsMissile oIsMissile = (_fnIsMissile)(Patchables::LolBase + fnIsMissile);

	return oIsMissile(this);
}

bool GameObject::IsMinion()
{
	typedef bool(__cdecl* _fnIsMinion)(GameObject* pObj);
	static _fnIsMinion oIsMinion = (_fnIsMinion)(Patchables::LolBase + fnIsMinion);

	return oIsMinion(this);
}

bool GameObject::IsTurret()
{
	typedef bool(__cdecl* _fnIsTurret)(GameObject* pObj);
	return false;
}

bool GameObject::IsInhibitor()
{
	typedef bool(__cdecl* _fnIsInhibitor)(GameObject* pObj);
	return false;
}

bool GameObject::IsTroyEnt()
{
	typedef bool(__cdecl* _fnIsTroyEnt)(GameObject* pObj);
	return false;
}

bool GameObject::IsNexus()
{
	typedef bool(__cdecl* _fnIsNexus)(GameObject* pObj);
	return false;
}

UnitType GameObject::GetType()
{
	//__try
	//{
	//	if (this == nullptr)
	//		return UnitType::Unknown;

	//	auto unitType = *reinterpret_cast<UnitType**>(this + static_cast<int>(Offsets::GameObject::Type));
	//	if (unitType != nullptr)
	//	{
	//		return (UnitType)(*unitType);
	//	}
	//}
	//__except (1)
	//{
	//}

	return UnitType::Unknown;
}

Vector3 GameObject::GetPos()
{
	if (this == nullptr)
	{
		return Vector3(0, 0, 0);
	}

	auto vec = reinterpret_cast<Vector3*>(this + static_cast<int>(Offsets::GameObject::Position));
	if (vec == nullptr)
	{
		return Vector3(0, 0, 0);
	}

	return Vector3(vec->x, vec->y, vec->z);
}

std::string GameObject::GetName()
{
	if (this == nullptr)
		return "Unknown";

	return reinterpret_cast<LolString*>(this + static_cast<int>(Offsets::GameObject::Name))->Get();
}
