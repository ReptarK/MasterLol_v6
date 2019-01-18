#pragma once
#include <SDK/math/Vector.hpp>

class Line3D
{
public:
	Line3D(Vector3 start = Vector3(0, 0, 0), Vector3 end = Vector3(0, 0, 0))
	{
		_src = start;
		_dest = end;
	}

	Vector3 GetSourcePosition() { return _src; }
	Vector3 GetDestPosition() { return _dest; }

private:
	Vector3 _src, _dest;
};
