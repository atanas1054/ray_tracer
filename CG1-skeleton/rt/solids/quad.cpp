#include <rt/solids/quad.h>

namespace rt 
{
	Quad::Quad(const Point& v1, const Vector& span1, const Vector& span2, CoordMapper* texMapper, Material* material)
		: Solid(texMapper, material), v1(v1), span1(span1), span2(span2)
	{
		v2 = v1 + span1;
		v3 = v2 + span2;
		v4 = v1 + span2;
	}

	Intersection Quad::intersect(const Ray& ray, float previousBestDistance) const 
	{
		float t12 = dot(cross((v2 - ray.o), (v1 - ray.o)), ray.d);
		float t23 = dot(cross((v3 - ray.o), (v2 - ray.o)), ray.d);
		float t34 = dot(cross((v4 - ray.o), (v3 - ray.o)), ray.d);
		float t41 = dot(cross((v1 - ray.o), (v4 - ray.o)), ray.d);
		if(
			(t12 > 0 && t23 > 0 && t34 > 0 && t41 > 0) 
			|| (t12 < 0 && t23 < 0 && t34 < 0 && t41 < 0)
			)
		{
			Vector normal = cross(span1, span2).normalize();
			float temp = dot(ray.d , normal);
			float distance = dot((v1 - ray.o), normal) / temp;
			if(distance > 0 && distance < previousBestDistance){
				float dir = dot(ray.o - v1, normal);
				if(dir < 0) {
					return Intersection(distance, ray, this, -normal, ray.getPoint(distance));
				} else if(dir > 0){
					return Intersection(distance, ray, this, normal, ray.getPoint(distance));
				}
			}
		}
		return Intersection::failure();
	}
	Point Quad::sample() const
	{ return Point(); }
    float Quad::getArea() const 
	{
		return cross(span1, span2).length() * 2;
	}

	BBox Quad::getBounds() const
	{
		float minimum_x = min(v1.x, min(v2.x, min(v3.x, v4.x)));
		float minimum_y = min(v1.y, min(v2.y, min(v3.y, v4.y)));
		float minimum_z = min(v1.z, min(v2.z, min(v3.z, v4.z)));

		float maximum_x = max(v1.x, max(v2.x, max(v3.x, v4.x)));
		float maximum_y = max(v1.y, max(v2.y, max(v3.y, v4.y)));
		float maximum_z = max(v1.z, max(v2.z, max(v3.z, v4.z)));

		return BBox(Point(minimum_x,minimum_y,minimum_z),Point(maximum_x,maximum_y,maximum_z));
	}

	Point Quad::getCenter() const 
	{
		return v1 + (span1 / 2) + (span2 / 2);
	}
}