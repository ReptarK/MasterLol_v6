#pragma once
#include "../IGameService.h"
#include <Common/Prediction.h>

class DebugPredictionService : public IGameService {
public:
	GameObject* mSelectedTarget;
	Common::PredictionOutput predictedOutput = Common::PredictionOutput(Common::PredictionInput());
	Vector3 predictedPosition;

	DebugPredictionService() {
		this->mSelectedTarget = nullptr;
		this->predictedPosition = Vector3();
	}

	virtual void OnUpdate();
	virtual void OnEndScene();
};

