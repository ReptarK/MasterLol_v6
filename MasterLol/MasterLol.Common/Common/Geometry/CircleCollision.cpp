#include "CircleCollision.h"
#include "LineCollision.h"

namespace Geometry
{
	bool CircleCollision::IsCollision( Circle3D otherCircle )
	{
		Vector3 pos2d = GetPos();
		pos2d.toGround();
		otherCircle.GetPos().toGround();

		float distance = pos2d.DistTo( otherCircle.GetPos() );
		return distance <= this->GetRadius() + otherCircle.GetRadius();
	}
}
