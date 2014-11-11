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
					//Vector normal = (center - point).normalize();
					Vector normal = (center - point).normalize();
					//Vector normal = dist
					return Intersection(dist, ray, this, normal, point);
				}
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
		return 0;
	}

}