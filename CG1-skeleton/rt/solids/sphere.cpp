#include <rt/solids/sphere.h>
#include <cmath>

namespace rt 
{

	Sphere::Sphere(const Point& center, float radius, CoordMapper* texMapper, Material* material) 
		: Solid(texMapper, material), radius(radius), center(center)
	{

	}

	Intersection Sphere::intersect(const Ray& ray, float previousBestDistance) const 
	{
		Vector temp = ray.o - Sphere::center;
		//check whether there is an intersection
		/*
		float s = cross(temp, ray.d).length() / ray.d.length();
		if(s < radius)
		{

			float c = dot(temp, temp) - radius * radius;
			float b = 2 * dot(temp, ray.d);
			float a = dot(ray.d, ray.d);
			float sqrt = std::sqrtf(b * b - 4 * a * c);
			float x1 = (- b + sqrt) / (2 * a);
			float x2 = (- b - sqrt) / (2 * a);
			if(x1 > 0 || x2 > 0){
				float dist = x1 < x2 ? x1 : x2;
				if(x1 < 0) dist = x2;
				if(x2 < 0) dist = x1;
				if(dist < previousBestDistance) {
					Point point = ray.getPoint(dist);
					float len = (point - center).length();
					Vector normal = (point - center).normalize();
					return Intersection(dist, ray, this, normal, point);
				}
			}

		}*/
		
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
			if( d1 > epsilon && d1 < d2 && d1 + epsilon < previousBestDistance){
				return Intersection(d1, ray, this, normal, local);
			}
			if(d2 > epsilon && d2 + epsilon < previousBestDistance){
				hitPoint = ray.getPoint(d2);
				normal = (hitPoint - center).normalize();
				local = Point(hitPoint.x - center.x, hitPoint.y - center.y, hitPoint.z - center.z);
				return Intersection(d2, ray, this, normal, local);
			}
		}
		return Intersection::failure();
	}

	Point Sphere::sample() const 
	{
		return Point();
	}
	float Sphere::getArea() const 
	{
		return 4 * pi * radius * radius;
	}

	 BBox Sphere::getBounds() const
	 {
		return BBox(Point(center - Vector::rep(radius)), Point(center + Vector::rep(radius)));
	 }

	 Point Sphere::getCenter() const
	 {
		return Point(center);
	 }

}