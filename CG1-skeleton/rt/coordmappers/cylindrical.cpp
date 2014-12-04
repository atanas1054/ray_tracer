#include <rt\coordmappers\cylindrical.h>

namespace rt{

	CylindricalCoordMapper::CylindricalCoordMapper(const Point& origin, const Vector& longitudinalAxis, const Vector& polarAxis)
	{

	}

    Point CylindricalCoordMapper::getCoords(const Intersection& hit) const
	{
		return Point();
	}
}