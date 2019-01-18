#pragma once
#include "Line3D.h"

#include "CircleCollision.h"

namespace Geometry
{
	class LineCollision
		: public Line3D
	{
	public:
		LineCollision( Vector3 src = Vector3( 0, 0, 0 ), Vector3 dest = Vector3( 0, 0, 0 ), float width = 1 )
			: Line3D( src, dest ) {
			_width = width;
		}

		float GetWidth() { return _width; }
		void SetWidth( float width ) { _width = width; }

		bool IsCollision( CircleCollision );
		bool IsCollision( Circle3D );

	private:
		float _width;
	};
}
