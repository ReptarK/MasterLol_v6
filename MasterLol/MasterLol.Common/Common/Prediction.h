#pragma once
#include <SDK/StaticEnums.h>
#include <SDK/ObjectManager.h>
#include <SDK/AIHeroClient.h>

namespace Common
{
	struct PredictionInput
	{
		Vector3 from = ObjectManager::GetPlayer()->GetPos();
		float delay = 0;
		float radius = 1.f;
		float range = FLT_MAX;
		float speed = FLT_MAX;
		ESpellCastType::ESpellCastType castType;
		Obj_AI_Base* target;
	};

	class PredictionOutput
	{
	public:
		PredictionOutput(PredictionInput input) {
			this->input = input;
			this->castPosition = ObjectManager::GetPlayer()->GetPos();
		}

		PredictionInput input;
		Vector3 castPosition;
		Vector3 predictedPosition;
	};

	class Prediction
	{
	public:
		static PredictionOutput GetPositionOnPath(PredictionInput input);

		static Vector3 BasicPrediction(Obj_AI_Base* target, float spellRadius, float spellRange, float missileSpeed, float castDelay);
	};
}
