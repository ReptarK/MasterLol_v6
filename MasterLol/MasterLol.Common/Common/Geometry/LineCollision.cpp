#include "LineCollision.h"

namespace Geometry
{
	bool LineCollision::IsCollision( CircleCollision circle )
	{
		return IsCollision( Circle3D( circle.GetPos(), circle.GetRadius() ) );
	}

	bool LineCollision::IsCollision( Circle3D circle )
	{
		Vector3 circleCenter = circle.GetPos();
		Vector3 vecEndStart = GetDestPosition() - GetSourcePosition();
		Vector3 vecCircleStart = circleCenter - GetSourcePosition();
		vecEndStart.y = 0;
		vecCircleStart.y = 0;

		Vector3 vecProjection = vecCircleStart.ProjectionOn( vecEndStart );
		// Transform projection to same direction as EndStart
		vecProjection = vecProjection.sameDirectionAs( vecEndStart );

		if ( vecProjection.Length() > vecEndStart.Length() )
		{
			vecProjection = vecEndStart; // == vecProjection = vecProjection.Normalized() * vecEndStart.Length();
			float angle = Vector3::angleBetween( circleCenter, GetDestPosition() );
			return ( GetDestPosition().DistTo( circleCenter ) < circle.GetRadius() );
		}
		else
		{
			Vector3 vecCircleToProjection = ( vecCircleStart - vecProjection );
			float distFromLineToCircle = vecCircleToProjection.Length();

			return GetWidth() + circle.GetRadius() >= distFromLineToCircle;
		}
	}
}
