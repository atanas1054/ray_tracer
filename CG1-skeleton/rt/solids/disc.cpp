#include <rt/solids/disc.h>

namespace rt 
{
	
	Disc::Disc(const Point& center, const Vector& normal, float radius, CoordMapper* texMapper, Material* material) 
		: Solid(texMapper, material), origin(center), radius(radius)
	{
		Disc::normal = normal.normalize();
	}

	Intersection Disc::intersect(const Ray& ray, float previousBestDistance) const 
	{
		float temp = dot(ray.d , normal);
		float distance = dot((origin - ray.o), normal) / temp;
		if(distance > 0){
			Point p = ray.getPoint(distance);
			if((p - origin).length() < radius && distance < previousBestDistance){
				float dir = dot(ray.o - origin, normal);
				if(dir < 0) {
					return Intersection(distance, ray, this, normal, p);
				} else if(dir > 0){
					return Intersection(distance, ray, this, -normal, p);
				}
			}
		}
		return Intersection::failure();
	}
	Point Disc::sample() const {
		return Point();
	}
	float Disc::getArea() const{
		return 0;
	}
}