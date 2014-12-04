#include <rt/coordmappers/plane.h>
#include <core/point.h>
#include <rt/intersection.h>
#include <rt/solids/solid.h>

namespace rt{

	PlaneCoordMapper::PlaneCoordMapper(const Vector& e1, const Vector& e2): e1(e1), e2(e2) {
		normal = cross(e1, e2).normalize();
	}

    Point PlaneCoordMapper::getCoords(const Intersection& hit) const
	{
		//assumes local hit = hit - center;
		Vector n = normal;
		Point center = hit.solid->getCenter();
		Vector local = hit.local() - Point::rep(0);
		if(dot(n, local) < 0)
		{
			n = -n;
		}


		return Point();
	}
}