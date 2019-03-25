#pragma once
#include "../../Option.h"

#include <SDK/Inputs.h>
#include <SDK/Draw.h>
#include <SDK/SpellCastInfo.h>
#include <SDK/Obj_AI_Base.h>
#include <SDK/EventManager.h>

class TimerService : public Singleton<TimerService> {
	friend class Singleton<TimerService>;
	//const float TIMEOUT = 

	TimerService() {
		this->mLastAttackTime = 0;
		this->mNextAttackTime = 0;
		this->mSentAttackTime = 0;
	}

public:
	float mLastAttackTime;
	float mNextAttackTime;
	float mSentAttackTime;

	bool CanMove();
	bool CanAttack();

	static void OnUpdate();
	static void OnProcessSpell(SpellCastInfo*, Obj_AI_Base* caster);
	static void OnEndScene();

	void Initialize()
	{
		EventHandler<EventIndex::OnUpdate, EventDefines::OnMainLoop>::GetInstance()->Add(this->OnUpdate);
		EventHandler<EventIndex::OnDrawingEndScene, EventDefines::OnDrawingEndScene, IDirect3DDevice9*>::GetInstance()->Add(this->OnEndScene);
		EventHandler<EventIndex::OnProcessSpell, EventDefines::OnProcessSpell, SpellCastInfo*, Obj_AI_Base*>::GetInstance()->Add(this->OnProcessSpell);
	}
};

