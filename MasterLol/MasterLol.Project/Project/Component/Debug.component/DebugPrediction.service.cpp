#include "DebugPrediction.service.h"

#include <SDK/HudManager.h>
#include <SDK/Game.h>
#include <SDK/SpellInclude.h>

#include <Common/ObjectHelper.h>


void DebugPredictionService::OnUpdate()
{
	if (!Option::Get().enable_debug_prediction) return;

	// Left click to select a Target
	if (GetAsyncKeyState(VK_LBUTTON) & 1) {
		this->mSelectedTarget = (HudManager::GetUnderMouseObject() ? HudManager::GetUnderMouseObject() : this->mSelectedTarget);
	}

	// Right click to unselect Target
	if (GetAsyncKeyState(VK_RBUTTON) & 1)
		this->mSelectedTarget = nullptr;

	if (!this->mSelectedTarget) return;
	AIHeroClient* player = ObjectManager::GetPlayer();
	if (!player) return;

	//auto spell = ObjectManager::GetPlayer()->GetSpellbook()->GetSpell(ESpellSlot::Q)->GetSpellInfo()->GetSpellData();
	//this->predictedPosition = Common::Prediction::BasicPrediction(
	//	(Obj_AI_Base*)this->mSelectedTarget,
	//	spell->MissileWidth,
	//	spell->CastRange[0],
	//	spell->MissileSpeed,
	//	0.675);

	//Common::PredictionInput pi = Common::PredictionInput();
	//pi.castType = ESpellCastType::Line;
	//pi.delay = 0.5f;
	//pi.from = player->GetPos();
	//pi.radius = 100;
	//pi.range = spell->CastRange[0];
	//pi.speed = FLT_MAX;
	//pi.target = (Obj_AI_Base*)this->mSelectedTarget;

	//this->predictedOutput = Common::Prediction::GetPositionOnPath(pi);
}

void BasicPrediction(Obj_AI_Base * target, float spellRadius, float spellRange, float missileSpeed, float castDelay)
{
	AIHeroClient* player = ObjectManager::GetPlayer();
	Navigation* navigation = target->GetNavigation();
	PathManager pathManager = navigation->mPathManager;
	auto pathList = pathManager.GetPathList();

	if (pathManager.GetSize() <= 1 || (target->GetSpellbook()->IsAutoAttacking() && !navigation->mIsDashing))
	{
		Draw.Line(player->GetPos(), target->GetPos(), 2, GREEN());
	}

	int ping = 40;
	float flytime_max = (missileSpeed != 0) ? spellRange / missileSpeed : 0.f;
	float t_min = castDelay + ping / 1000.f;
	float t_max = flytime_max + castDelay + ping / 1000.f;
	float path_time = 0.f;


	int path_bounds_index[2] = { -1, -1 };

	for (int i = 0; i < pathList.size(); ++i)
	{
		Vector3 cur = pathManager.mPath[i].toGround();	//skills hit calculating in 2d space
		Vector3 next = pathManager.mPath[i + 1].toGround();
		float t = next.DistTo(cur) / target->GetUnitStats()->mMoveSpeed;

		if (path_time <= t_min && path_time + t >= t_min)
			path_bounds_index[0] = i;
		if (path_time <= t_max && path_time + t >= t_max)
			path_bounds_index[1] = i;
		if (path_bounds_index[0] >= 0 && path_bounds_index[1] >= 0)
			break;

		path_time += t;
	}

	//if skill will hit to the target within the boundaries
	if (path_bounds_index[0] >= 0 && path_bounds_index[1] >= 0)
	{
		int curr_path_index = path_bounds_index[0];
		while (true)
		{
			Vector3 cur = pathManager.mPath[curr_path_index].toGround();
			Vector3 next = pathManager.mPath[curr_path_index + 1].toGround();

			Vector3 direction = (next - cur).Normalized();

			float extender = target->GetBoundingRadius();
			float distance = spellRadius;

			int steps = (int)floor(cur.DistTo(next) / distance);

			if (steps > 0 && steps < 1000)
			{
				for (int i = 1; i < steps - 1; i++)
				{
					Vector3 center = cur + direction * distance * i;
					Vector3 pt_a = center - direction * extender;
					Vector3 pt_b = center + direction * extender;

					float flytime = (missileSpeed != 0) ? player->GetPos().DistTo(target->GetPos()) / missileSpeed : 0.f;
					float t = flytime + castDelay + ping / 1000.f;

					float arrive_time_a = target->GetPos().DistTo(pt_a) / target->GetUnitStats()->mMoveSpeed;
					float arrive_time_b = target->GetPos().DistTo(pt_b) / target->GetUnitStats()->mMoveSpeed;
					// TEST
					arrive_time_a /= 1;
					arrive_time_b /= 1;

					Vector3 predicted_pos = center;

					if (min(arrive_time_a, arrive_time_b) <= t && max(arrive_time_a, arrive_time_b) >= t)
					{
						Draw.Line(target->GetPos(), cur, 2, GREEN());
						Draw.Line(target->GetPos(), next, 2, BLUE());
						return;

					}
				}
			}

			if (curr_path_index == path_bounds_index[1])
				break;

			++curr_path_index;
		}
	}

	return;
}

Vector3* test1(Obj_AI_Base * target, float spellRadius, float spellRange, float missileSpeed, float castDelay)
{
	AIHeroClient* player = ObjectManager::GetPlayer();
	Navigation* navigation = target->GetNavigation();
	PathManager pathManager = navigation->mPathManager;
	auto pathList = pathManager.GetPathList();
	float pathLength = pathManager.GetPathLength();
	Draw.TextArg("%.0f", player->GetPos(), text_alignment::centered, 0, false, GREEN(), 0, pathLength);

	float elapsedTime = 2;
	float speed = target->GetUnitStats()->mMoveSpeed;

	Vector3 result[2];

	float total_time = 0;
	Vector3 lastWaypoint = target->GetPos();
	for (auto waypoint : pathList)
	{
		total_time += waypoint.DistTo(lastWaypoint) / speed;
		if (total_time > elapsedTime) {
			//Draw.Line(lastWaypoint, waypoint, 2, GREEN());
			result[0] = lastWaypoint;
			result[1] = waypoint;
			return result;
		}
		lastWaypoint = waypoint;
	}

	return result;
}

void DebugPredictionService::OnEndScene()
{
	if (!Option::Get().enable_debug_prediction) return;
	if (!this->mSelectedTarget) return;
	Draw.RangeCircle(this->mSelectedTarget->GetPos(), this->mSelectedTarget->GetBoundingRadius(), YELLOW(), 1);

	//if (!this->predictedPosition.IsValid()) return;
	AIHeroClient* player = ObjectManager::GetPlayer();
	if (!player) return;

	auto spell = ObjectManager::GetPlayer()->GetSpellbook()->GetSpell(ESpellSlot::Q)->GetSpellInfo()->GetSpellData();
	//BasicPrediction(
	//	(Obj_AI_Base*)this->mSelectedTarget,
	//	spell->MissileWidth,
	//	spell->CastRange[0],
	//	spell->MissileSpeed,
	//	1);

	static Vector3 r[2];
	if (GetAsyncKeyState(VK_RBUTTON) & 1) {
		auto result = test1(player, spell->MissileWidth, spell->CastRange[0], spell->MissileSpeed, 1);
		r[0] = result[0];
		r[1] = result[1];
		printf("HELLO!");

	}

	if (r[0].IsValid() && r[1].IsValid()) {

		Draw.Line(r[0], r[1], 2, GREEN());
	}
}

