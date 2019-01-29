#include "BasicVisuals.h"

#include <SDK/Options.h>
#include <SDK/ObjectManager.h>
#include <SDK/Obj_AI_Turret.h>
#include <SDK/Draw.h>

void RenderPlayer(AIHeroClient * player)
{
	if ( !player->IsAlive() )
		return;

	auto addRadius = player->GetBoundingRadius();

	if ( g_Options.show_AA_range )
		Draw.RangeCircle( player->GetPos(), player->GetUnitStats()->mAttackRange + addRadius, YELLOW(), 0.2 );
}

void RenderTurrets( AIHeroClient * player )
{
	auto units = ObjectManager::GetUnitArray();
	auto playerPos = player->GetPos();

	for ( int i = 0; i < ObjectManager::GetHighestObjectId(); ++i )
	{
		auto unit = units[i];

		if ( !unit->IsTurret() )
			continue;
		if ( *unit->GetTeam() == *player->GetTeam() )
			continue;

		Obj_AI_Turret * turret = ( Obj_AI_Turret * )unit;
		auto addRadius = turret->GetBoundingRadius();
		Vector3 turretPos = turret->GetPos();
		float attackRangeSqr = turret->GetAttackRange() * turret->GetAttackRange();

		if ( turretPos.DistToSqr( playerPos ) < attackRangeSqr * 2 )
			Draw.RangeCircle( unit->GetPos(), turret->GetAttackRange(), RED(), 0.2 );
	}
}

void BasicVisuals::OnEndScene( LPDIRECT3DDEVICE9 device )
{
	auto player = ObjectManager::GetPlayer();
	if ( !player ) return;

	RenderPlayer( player );
	RenderTurrets( player );
}

void BasicVisuals::Initialize()
{
	EventHandler<EventIndex::OnDrawingEndScene, EventDefines::OnDrawingEndScene, IDirect3DDevice9*>::GetInstance()->Add( BasicVisuals::OnEndScene );
}
