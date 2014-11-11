#include <rt/solids/triangle.h>
#include <core/point.h>

namespace rt 
{
	Triangle::Triangle(Point vertices[3], CoordMapper* texMapper, Material* material)
		: Solid(texMapper, material)
	{
		v1 = vertices[0];
		v2 = vertices[1];
		v3 = vertices[2];
	}
	Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3, CoordMapper* texMapper, Material* material) 
		: Solid(texMapper, material), v1(v1), v2(v2), v3(v3) { }

	Intersection Triangle::intersect(const Ray& ray, float previousBestDistance) const 
	{
		float t12 = dot(cross((v2 - ray.o), (v1 - ray.o)), ray.d);
		float t23 = dot(cross((v3 - ray.o), (v2 - ray.o)), ray.d);
		float t31 = dot(cross((v1 - ray.o), (v3 - ray.o)), ray.d);
		if(
			(t12 > 0 && t23 > 0 && t31 > 0) 
			|| (t12 < 0 && t23 < 0 && t31 < 0)
			) 
		{
			float sum = t12 + t23 + t31;
			float x = t23 / sum;
			float y = t31 / sum;
			float z = t12 / sum;
			
			Point p = x * v1 + (y * v2 - Point(0,0,0)) + (z * v3 - Point(0,0,0));
			float distance = (p - ray.o).length();
			if(distance > 0 && distance < previousBestDistance){
				Vector normal = cross(v2 - v1, v3 - v1).normalize();
				if(dot(ray.o - v1, normal) < 0){
					return Intersection(distance, ray, this, normal, Point(x, y, z));
				} else {
					return Intersection(distance, ray, this, -normal, Point(x, y, z));
				}
			}
		}
		return Intersection::failure();
	}
	Point Triangle::sample() const {
		return Point();
	}
	float Triangle::getArea() const {
		return 0;
	}
}