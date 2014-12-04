#include <rt/coordmappers/spherical.h>

namespace rt{

	SphericalCoordMapper::SphericalCoordMapper()
	{

	}

    SphericalCoordMapper::SphericalCoordMapper(const Point& origin, const Vector& zenith, const Vector& azimuthRef)
	{

	}

    Point SphericalCoordMapper::getCoords(const Intersection& hit) const
	{
		return Point();
	}
}