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
		Point center = Point::rep(0);
		Point local = hit.local();
		if(dot(n, local - center) > 0)
		{
			n = -n;
		}
		//intersect ray (local, n) to plane (center, n)
		float temp = dot(n , n);
		float distance = dot((center - local), n) / temp;
		Point hp = local + ((n * distance) / n.length());
		//calculate uv
		float u = (hp - center).length() * dot((hp - center).normalize(), e1.normalize()) / e1.length();
		float v = (hp - center).length() * dot((hp - center).normalize(), e2.normalize()) / e2.length();
		return Point(u, v, 0);
	}
}