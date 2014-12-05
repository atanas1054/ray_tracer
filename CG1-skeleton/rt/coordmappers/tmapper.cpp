#include <rt/coordmappers/tmapper.h>
#include <rt/intersection.h>

namespace rt{

	TriangleMapper::TriangleMapper(const Point& tv0, const Point& tv1, const Point& tv2) 
		: tv0(tv0), tv1(tv1), tv2(tv2) { }

    TriangleMapper::TriangleMapper(Point ntv[3])
		: tv0(ntv[0]), tv1(ntv[1]), tv2(ntv[2]) { }

    Point TriangleMapper::getCoords(const Intersection& hit) const
	{
		Point bary = hit.local();
		return Point(
			tv0.x * bary.x + tv1.x * bary.y + tv2.x * bary.z,
			tv0.y * bary.x + tv1.y * bary.y + tv2.y * bary.z,
			tv0.z * bary.x + tv1.z * bary.y + tv2.z * bary.z
		);
	}
}

