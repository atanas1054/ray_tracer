#include <rt/solids/infiniteplane.h>
#include <cmath>

namespace rt
{
	InfinitePlane::InfinitePlane(const Point& origin, const Vector& normal, CoordMapper* texMapper, Material* material): 
	Solid(texMapper, material), origin(origin)
	{
		InfinitePlane::normal = normal.normalize();
	}

	Intersection InfinitePlane::intersect(const Ray& ray, float previousBestDistance) const 
	{
		float temp = dot(ray.d , normal);
		float distance = dot((origin - ray.o), normal) / temp;
		
		if(distance > 0 && distance < previousBestDistance){
			float dir = dot(ray.o - origin, normal);
			if(dir < 0) {
				return Intersection(distance, ray, this, normal, ray.getPoint(distance));
			} else if(dir > 0){
				return Intersection(distance, ray, this, -normal, ray.getPoint(distance));
			}
		}
		return Intersection::failure();
	}

	Point InfinitePlane::sample() const 
	{
		return Point();
	}
	float InfinitePlane::getArea() const 
	{
		return 0;
	}
}