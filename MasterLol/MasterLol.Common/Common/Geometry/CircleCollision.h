#pragma once
#include "Circle3D.h"
#include <SDK/Obj_AI_Base.h>

namespace Geometry
{
	class LineCollision;

	class CircleCollision
		: public Circle3D
	{
	public:
		CircleCollision( Obj_AI_Base* object = nullptr, float radius = 1 ) : Circle3D( object->GetPos(), radius ) {
			_object = object;
		}

		Obj_AI_Base* GetAIObject() { return _object; }
		void SetAIObject( Obj_AI_Base* object ) { _object = object; }

		virtual Vector3 GetPos() { return GetAIObject()->GetPos()/* + GetAIObject()->GetAIManager_Client()->pNavigation->vVelocity * 5*/; }

		bool IsCollision( Circle3D );

	private:
		Obj_AI_Base * _object;
	};
}
