#include <rt/coordmappers/plane.h>
#include <core\point.h>

namespace rt{

	PlaneCoordMapper::PlaneCoordMapper(const Vector& e1, const Vector& e2)
	{

	}

    Point PlaneCoordMapper::getCoords(const Intersection& hit) const
	{
		return Point();
	}
}