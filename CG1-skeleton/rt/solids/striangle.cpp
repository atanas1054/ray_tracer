#include <rt/solids/striangle.h>
#include <core/random.h>
#include <iostream>

namespace rt{


	SmoothTriangle::SmoothTriangle(Point vertices[3], Vector normals[3], CoordMapper* texMapper, Material* material): Triangle(vertices,texMapper, material)
	{
		v1 = vertices[0];
		v2 = vertices[1];
		v3 = vertices[2];
		n1 = normals[0];
		n2 = normals[1];
		n3 = normals[2];
	}
    SmoothTriangle::SmoothTriangle(const Point& v1, const Point& v2, const Point& v3, 
        const Vector& n1, const Vector& n2, const Vector& n3, 
        CoordMapper* texMapper, Material* material)
		: Triangle(v1,v2,v3,texMapper, material), v1(v1), v2(v2), v3(v3),n1(n1),n2(n2),n3(n3)
	{

	}

    Intersection SmoothTriangle::intersect(const Ray& ray, float previousBestDistance) const
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

			if(dot(ray.d, p - ray.o) > 0) {
				if(distance > epsilon && distance + epsilon < previousBestDistance){
					  //find barrycentric coordinates v,w,u
						/*
					  Vector normal_ = cross(v2 - v1, v3 - v1).normalize();
					  float areaABC = dot( normal_, cross( (v2 - v1), (v3 - v1) )  ) ;
					  float areaPBC = dot( normal_, cross( (v2 - p), (v3 - p) )  ) ;
					  float areaPCA = dot( normal_, cross( (v3 - p), (v1 - p) )  );

					  float v = areaPBC / areaABC ; 
					  float w = areaPCA / areaABC ;
					  float u  = 1.0f - v - w ; 
						*/
					  //find the interpolated normal (using the barrycentric coordinates)
					 Vector normal = x*n1 + y*n2 + z*n3;
					if(dot(ray.o - v1, normal) < 0){
						return Intersection(distance, ray, this, -normal, Point(x, y, z));
					} else {
						return Intersection(distance, ray, this, normal, Point(x, y, z));
					}
				}
			}
		}
		return Intersection::failure();
	}

	Point SmoothTriangle::sample() const {
		Vector b = Vector(random(), random(), random());
		b = b / (b.x + b.y + b.z);
		return Point(
			v1.x * b.x + v2.x * b.y + v3.x * b.z,
			v1.y * b.x + v2.y * b.y + v3.y * b.z,
			v1.z * b.x + v2.z * b.y + v3.z * b.z
		);
	}

	float SmoothTriangle::getArea() const {
		return cross(v1 - v3, v1 - v2).length() / 2;
	}

	BBox SmoothTriangle::getBounds() const
	{
		return BBox(Point(min(v1.x,min(v2.x,v3.x)),min(v1.y,min(v2.y,v3.y)),min(v1.z,min(v2.z,v3.z))),Point(max(v1.x,max(v2.x,v3.x)),max(v1.y,max(v2.y,v3.y)),max(v1.z,max(v2.z,v3.z))));
	}

	Point SmoothTriangle::getCenter() const
	{
		return Point((v1.x+v2.x+v3.x)/3,(v1.y+v2.y+v3.y)/3,(v1.z+v2.z+v3.z)/3);
	}
}