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
		/*
		//assumes local hit = hit - center;
		Vector dir = normal;
		Point center = Point::rep(0);
		Point local = hit.hitPoint();
		if(dot(dir, local - center) > 0)
		{
			dir = -dir;
		}
		//intersect ray (local, n) to plane (center, n)
		float temp = dot(dir , -dir);
		float distance = dot((center - local), -dir) / temp;
		Point hp = local + ((dir * distance) / dir.length());
		//calculate uv

		float u = (hp - center).length() * dot((hp - center).normalize(), e1.normalize()) / e1.length();
		float v = (hp - center).length() * dot((hp - center).normalize(), e2.normalize()) / e2.length();
		*/
		
		//Vector localV = hit.local() - Point::rep(0);
		Vector localV = hit.hitPoint() - Point::rep(0);
		float dist = localV.length();
		float u = dist * (dot(e1, localV) / dist / e1.length()) / e1.length();
		float v = dist * (dot(e2, localV) / dist / e2.length()) / e2.length();
		
		return Point(u, v, 0);
	}
}