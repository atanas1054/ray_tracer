#include <rt/intersection.h>
#include <rt/ray.h>
#include <rt/solids/solid.h>
#include <core/vector.h>
#include <core/point.h>

namespace rt 
{
	
	Intersection Intersection::failure() {
		return Intersection();
	}

    Intersection::Intersection(float distance, const Ray& ray, const Solid* solid, const Vector& normal, const Point& uv) 
		:ray(ray), solid(solid), distance(distance), _normal(normal), _local(uv)
	{
		isIntersect = true;
	}

	//not implemented
    Point Intersection::hitPoint() const{
		return Point();
	}

	Vector Intersection::normal() const {
		return _normal;
	}
    Point Intersection::local() const {
		return _local;
	}

	//this allows intersection object to be put directly in conditional statements. Becomes true iff there is an intersection
    Intersection::operator bool() {
		return isIntersect;	
	}

}