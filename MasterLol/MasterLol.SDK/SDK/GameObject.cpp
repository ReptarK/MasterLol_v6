#include "stdafx.h"
#include "GameObject.h"
#include "GameObjectVTable.h"

GameObjectVTable * GameObject::GetVirtual()
{
	return reinterpret_cast< GameObjectVTable* >( this );
}

template< typename Function > Function CallVirtual( PVOID Base, DWORD Index )
{
	PDWORD* VTablePointer = ( PDWORD* )Base;
	PDWORD VTableFunctionBase = *VTablePointer;
	DWORD dwAddress = VTableFunctionBase[Index];

	return ( Function )( dwAddress );
}

float GameObject::GetBoundingRadius()
{
	__try
	{
		return this->GetVirtual()->BoundingRadius();

	}
	__except ( 1 ) { return 0; }
}

ObjectType * GameObject::GetObjectTypeName()
{
	int v1; // edi@1
	unsigned int v2; // ecx@2
	unsigned int EncryptedId; // esi@2
	int v4; // edx@3
	unsigned __int8 v5; // al@5
	unsigned int i; // eax@6
	bool result; // al@8

	int gameObjectCopy = ( int )this;
	v1 = gameObjectCopy;
	if ( gameObjectCopy )
	{
		v2 = 0;
		EncryptedId = *( BYTE * )( gameObjectCopy + 28 );
		gameObjectCopy = *( DWORD * )( gameObjectCopy + 4 * *( BYTE * )( gameObjectCopy + 5 ) + 8 );
		if ( EncryptedId )
		{
			v4 = v1 + 24;
			do
			{
				v4 += 4;
				*( &gameObjectCopy + v2 ) ^= *( DWORD * )( v4 - 4 ) ^ XOR_KEY;
				++v2;
			} while ( v2 < EncryptedId );
		}
		v5 = *( BYTE * )( v1 + 29 );
		if ( v5 )
		{
			for ( i = 4 - v5; i < 4; ++i )
				*( ( BYTE * )&gameObjectCopy + i ) ^= *( BYTE * )( v1 + i + 24 ) ^ 0xC4;
		}
	}
	else
	{
		result = 0;
	}
	return ( ObjectType* )gameObjectCopy;
}

EUnitType GameObject::GetUnitId()
{
	int v2; // eax@1
	int v3; // esi@1
	unsigned int v4; // ecx@1
	unsigned int v5; // edi@1
	int *v6; // edx@2
	int v7; // eax@3
	unsigned __int8 v8; // al@4
	unsigned int i; // eax@5
	int objectId; // [sp+8h] [bp-4h]@1

	int objectCpy = ( int )this;


	v2 = *( BYTE * )( objectCpy + 81 );
	v3 = objectCpy + 80;
	v4 = 0;
	v5 = *( BYTE * )( v3 + 24 );
	objectId = *( DWORD * )( v3 + 4 * v2 + 4 );
	if ( v5 )
	{
		v6 = ( int * )( v3 + 20 );
		do
		{
			v7 = *v6;
			++v6;
			*( &objectId + v4 ) ^= v7 ^ XOR_KEY;
			++v4;
		} while ( v4 < v5 );
	}
	v8 = *( BYTE * )( v3 + 25 );
	if ( v8 )
	{
		for ( i = 4 - v8; i < 4; ++i )
			*( ( BYTE * )&objectId + i ) ^= *( BYTE * )( v3 + i + 20 ) ^ 0xC4;
	}
	objectId |= objectId >> 1;
	objectId |= objectId >> 2;
	objectId |= objectId >> 4;
	objectId |= objectId >> 8;
	objectId |= objectId >> 16;

	objectId = objectId + 1;
	return (EUnitType)( objectId >> 1 );
}

bool GameObject::IsUnitId(EUnitType id )
{
	return ( id == this->GetUnitId() );
}

bool GameObject::IsHero()
{
	typedef bool( __cdecl* _fnIsHero )( GameObject* pObj );
	static _fnIsHero oIsHero = ( _fnIsHero )( Patchables::LolBase + fnIsHero );

	return oIsHero( this );
}

bool GameObject::IsMissile()
{
	typedef bool( __cdecl* _fnIsMissile )( GameObject* pObj );
	static _fnIsMissile oIsMissile = ( _fnIsMissile )( Patchables::LolBase + fnIsMissile );

	return oIsMissile( this );
}

bool GameObject::IsMinion()
{
	typedef bool( __cdecl* _fnIsMinion )( GameObject* pObj );
	static _fnIsMinion oIsMinion = ( _fnIsMinion )( Patchables::LolBase + fnIsMinion );

	return oIsMinion( this );
}

bool GameObject::IsTurret()
{
	typedef bool( __cdecl* _fnIsTurret )( GameObject* pObj );
	static _fnIsTurret oIsTurret = ( _fnIsTurret )( Patchables::LolBase + fnIsTurret );

	return oIsTurret( this );
}

bool GameObject::IsInhibitor()
{
	typedef bool( __cdecl* _fnIsInhibitor )( GameObject* pObj );
	static _fnIsInhibitor oIsInhibitor = ( _fnIsInhibitor )( Patchables::LolBase + fnIsInhib );

	return oIsInhibitor( this );
}

bool GameObject::IsTroy()
{
	typedef bool( __cdecl* _fnIsTroyEnt )( GameObject* pObj );
	static _fnIsTroyEnt oIsTroyEnt = ( _fnIsTroyEnt )( Patchables::LolBase + fnIsTroy );

	return oIsTroyEnt( this );
}

bool GameObject::IsNexus()
{
	typedef bool( __cdecl* _fnIsNexus )( GameObject* pObj );
	static _fnIsNexus oIsNexus = ( _fnIsNexus )( Patchables::LolBase + fnIsNexus );

	return oIsNexus( this );
}

bool GameObject::IsDragon()
{
	typedef bool( __thiscall* _fnIsDragon )( GameObject* pObj );
	static _fnIsDragon oIsDragon = ( _fnIsDragon )( Patchables::LolBase + fnIsDragon );

	return this->IsMinion() && oIsDragon( this );
}

bool GameObject::IsBaron()
{
	typedef bool( __thiscall* _fnIsBaron )( GameObject* pObj );
	static _fnIsBaron oIsBaron = ( _fnIsBaron )( Patchables::LolBase + fnIsBaron );

	return this->IsMinion() && oIsBaron( this );
}

EUnitType GameObject::GetType()
{
	if ( IsTroy() ) return EUnitType::Troy;
	if ( IsMinion() )
	{
		if ( IsDragon() ) return EUnitType::Dragon;
		if ( IsBaron() ) return EUnitType::Baron;
		return EUnitType::Minion;
	}
	if ( IsMissile() ) return EUnitType::Missile;
	if ( IsTurret() ) return EUnitType::Turret;
	if ( IsHero() ) return EUnitType::Hero;
	if ( IsInhibitor() ) return EUnitType::Inhibitor;
	if ( IsNexus() ) return EUnitType::Nexus;

	return EUnitType::Unknown;
}

Vector3 GameObject::GetPos()
{
	if ( this == nullptr )
	{
		return Vector3();
	}

	auto vec = reinterpret_cast< Vector3* >( this + ( int )( Offsets::GameObject::Position ) );
	if ( vec == nullptr )
	{
		return Vector3();
	}

	return *vec;
}

bool GameObject::GetHpBarPosition(Vector3* out)
{
	typedef int(__thiscall* _fnBaseDrawPosition)(GameObject* object, Vector3* position);
	static _fnBaseDrawPosition oBaseDrawPosition = (_fnBaseDrawPosition)(Patchables::LolBase + fnBaseDrawPosition);

	typedef int(__cdecl* _fnWorldToScreen)(Vector3* world, Vector3* screen);
	static _fnWorldToScreen oWorldToScreen = (_fnWorldToScreen)(Patchables::LolBase + fnWorldToScreen);

	Vector3 baseDrawPosition;
	Vector3 screen;
	oBaseDrawPosition(this, &baseDrawPosition);
	oWorldToScreen(&baseDrawPosition, &screen);
	float delta = abs(baseDrawPosition.y - this->GetPos().y);
	delta *= 5 / 6.0f;
	if (!oWorldToScreen(&baseDrawPosition, out))
		return false;

	out->x -= 60;
	out->y -= delta;
	out->z = 0;
	return true;

}

std::string GameObject::GetName()
{
	if ( this == nullptr )
		return "Unknown";

	return reinterpret_cast< LolString* >( this + static_cast< int >( Offsets::GameObject::Name ) )->Get();
}
