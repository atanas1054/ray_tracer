#include <rt/solids/aabox.h>
#include <rt/intersection.h>

namespace rt 
{
	AABox::AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material) 
		: Solid(texMapper, material), corner1(corner1), corner2(corner2)
	{
		
	}

	Intersection AABox::intersect(const Ray& ray, float previousBestDistance) const 
	{
		float dist = FLT_MAX;
		//
		float tx1 = (corner1.x - ray.o.x) / ray.d.x;
		float tx2 = (corner2.x - ray.o.x) / ray.d.x;
		float ty1 = (corner1.y - ray.o.y) / ray.d.y;
		float ty2 = (corner2.y - ray.o.y) / ray.d.y;
		float tz1 = (corner1.z - ray.o.z) / ray.d.z;
		float tz2 = (corner2.z - ray.o.z) / ray.d.z;
		//
		float nx, fx, ny, fy, nz, fz;
		if(tx1 < tx2) { nx = tx1; fx = tx2; } else { nx = tx2; fx = tx1; }
		if(ty1 < ty2) { ny = ty1; fy = ty2; } else { ny = ty2; fy = ty1; }
		if(tz1 < tz2) { nz = tz1; fz = tz2; } else { nz = tz2; fz = tz1; }
		//
		int sidex = 0;
		int sidey = 1;
		int sidez = 2;
		int sidenmax = -1;
		float nmax, fmin;
		if(nx > ny) { nmax = nx; sidenmax = sidex; } else { nmax = ny; sidenmax = sidey; }
		if(nmax > nz) { } else { nmax = nz; sidenmax = sidez; }
		fmin = fx < fy ? fx : fy;
		fmin = fmin < fz ? fmin : fz;
		//
		if(nmax < fmin && nmax < previousBestDistance) {
			Point p = ray.getPoint(nmax);
			Vector normal;
			if(sidenmax == sidex)
			{
				normal = Vector(1, 0, 0);
				if(dot(p - ray.o, normal) < 0) normal = -normal;
			} 
			else if(sidenmax == sidey)
			{
				normal = Vector(0, 1, 0);
				if(dot(p - ray.o, normal) < 0) normal = -normal;
			}
			else
			{
				normal = Vector(0, 0, 1);
				if(dot(p - ray.o, normal) < 0) normal = -normal;
			}
			return Intersection(nmax, ray, this, normal, p);
		}
		return Intersection::failure();
	}

	Point AABox::sample() const 
	{
		return Point();
	}
	float AABox::getArea() const 
	{
		return 0;
	}
}