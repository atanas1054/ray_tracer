#include <rt/groups/csgsolids/CSGSphere.h>

namespace rt 
{
	CSGSphere::CSGSphere(const Point& center, float radius, CoordMapper* texMapper, Material* material) 
		: CSG(CSG::CombineType::UNION, texMapper, material), radius(radius), center(center) { }
	
	std::vector<Intersection*> CSGSphere::intersections(const Ray& ray) const 
	{
		Vector temp = ray.o - CSGSphere::center;
		
		Vector co = ray.o - center;
		float coLength = co.length();
		float temp2 = dot(ray.d, co);
		float det = temp2 * temp2  - coLength * coLength + radius * radius;
		std::vector<Intersection*> intersections;
		if(det > 0)
		{
			float d1 = -temp2 + sqrt(det);
			float d2 = -temp2 - sqrt(det);
			if(d1 > d2)
			{
				float temp = d1;
				d1 = d2;
				d2 = temp;
			}
			//
			Point hitPoint = ray.getPoint(d1);
			Vector normal = (hitPoint - center).normalize();
			Point local = Point(hitPoint.x - center.x, hitPoint.y - center.y, hitPoint.z - center.z);
			intersections.push_back(new Intersection(d1, ray, this, normal, local));
			//
			hitPoint = ray.getPoint(d2);
			normal = (center - hitPoint).normalize();
			local = Point(hitPoint.x - center.x, hitPoint.y - center.y, hitPoint.z - center.z);
			intersections.push_back(new Intersection(d2, ray, this, normal, local));
		}
		return intersections;
	}

	Intersection CSGSphere::intersect(const Ray& ray, float previousBestDistance) const 
	{
		Vector temp = ray.o - CSGSphere::center;
		
		Vector co = ray.o - center;
		float coLength = co.length();
		float temp2 = dot(ray.d, co);
		float det = temp2 * temp2  - coLength * coLength + radius * radius;
		if(det > 0)
		{
			float d1 = -temp2 + sqrt(det);
			float d2 = -temp2 - sqrt(det);
			Point hitPoint = ray.getPoint(d1);
			Vector normal = (hitPoint - center).normalize();
			Point local = Point(hitPoint.x - center.x, hitPoint.y - center.y, hitPoint.z - center.z);
			if( d1 > 0 && d1 < d2 && d1 < previousBestDistance){
				return Intersection(d1, ray, this, normal, local);
			}
			if(d2 > 0 && d2 < previousBestDistance){
				hitPoint = ray.getPoint(d2);
				normal = (hitPoint - center).normalize();
				local = Point(hitPoint.x - center.x, hitPoint.y - center.y, hitPoint.z - center.z);
				return Intersection(d2, ray, this, normal, local);
			}
		}
		return Intersection::failure();
	}

	Point CSGSphere::sample() const 
	{
		return Point();
	}
	float CSGSphere::getArea() const 
	{
		return 4 * pi * radius * radius;
	}

	 BBox CSGSphere::getBounds() const
	 {
		return BBox(Point(center - Vector::rep(radius)), Point(center + Vector::rep(radius)));
	 }

	 Point CSGSphere::getCenter() const
	 {
		return Point(center);
	 }
}
