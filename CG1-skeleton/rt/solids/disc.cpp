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
					return Intersection(distance, ray, this, -normal, p);
				} else if(dir > 0){
					return Intersection(distance, ray, this, normal, p);
				}
			}
		}
		return Intersection::failure();
	}
	Point Disc::sample() const {
		return Point();
	}
	float Disc::getArea() const{
		return 2 * pi * radius * radius;
	}

	 BBox Disc::getBounds() const
	 {
		 //get a vector from the plane, perpendicular to the normal
		//if normal is (a,b,c) then a perpendicular vector is (c,c,-a-b)
		Vector vec(normal.z,normal.z,-normal.x-normal.y);

		//get unit vector
		vec = vec/vec.length();

		float hypot = sqrt(radius*radius + radius*radius);
		//get the extent of the disc
		Point p(origin.x +hypot*vec.x,origin.y +hypot*vec.y,origin.z +hypot*vec.z);
		Point p_(origin.x -hypot*vec.x,origin.y -hypot*vec.y,origin.z -hypot*vec.z);

		return BBox(Point(min(p.x,p_.x),min(p.y,p_.y),min(p.z,p_.z)),Point(max(p.x,p_.x),max(p.y,p_.y),max(p.z,p_.z)));

	 }

	 Point Disc::getCenter() const 
	 {
		return Point(origin);
	 }
}