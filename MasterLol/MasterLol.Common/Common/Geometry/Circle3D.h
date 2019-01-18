#include <SDK/math/Vector.hpp>

namespace Geometry
{
	class Circle3D
	{
	public:
		Circle3D( Vector3 centerPoint = Vector3( 0, 0, 0 ), float radius = 0 );

		float GetRadius() { return _radius; }

		virtual Vector3 GetPos() { return _centerPoint; }

	private:
		Vector3 _centerPoint;
		float _radius;
	};
}


