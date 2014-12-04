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
		Point hit = ray.getPoint(distance);
		Point local = Point(hit.x - origin.x, hit.y - origin.y, hit.z - origin.z);
		if(distance > 0 && distance < previousBestDistance){
			float dir = dot(ray.o - origin, normal);
			if(dir < 0) {
				return Intersection(distance, ray, this, -normal, local);
			} else if(dir > 0){
				return Intersection(distance, ray, this, normal, local);
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

	BBox InfinitePlane::getBounds() const
	{
		//get a vector from the plane, perpendicular to the normal
		//if normal is (a,b,c) then a perpendicular vector is (c,c,-a-b)
		Vector vec(normal.z,normal.z,-normal.x-normal.y);

		//infinite bbox
		return BBox(Point(vec.x,vec.y,vec.z)*(-FLT_MAX),Point(vec.x,vec.y,vec.z)*(FLT_MAX));
	}

	Point InfinitePlane::getCenter() const 
	{
		return Point(origin);
	}
}