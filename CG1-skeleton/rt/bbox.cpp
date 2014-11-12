#include <rt/bbox.h>
#include <rt/ray.h>
#include <algorithm> 

namespace rt{

	BBox BBox::empty()
	{
		return BBox();
	}

	BBox BBox::full()
	{
		return BBox(Point(FLT_MIN,FLT_MIN,FLT_MIN),Point(FLT_MAX,FLT_MAX,FLT_MAX));
	}

	void BBox::extend(const Point& point)
	{
		if (point.x<min1.x) min1.x = point.x;
		if (point.y<min1.y) min1.y = point.y;
		if (point.z<min1.z) min1.z = point.z;

		if (point.x>max1.x) max1.x = point.x;
		if (point.y>max1.y) max1.y = point.y;
		if (point.z>max1.z) max1.z = point.z;

	}

	void BBox::extend(const BBox& bbox)
	{
		extend(bbox.min1);
		extend(bbox.max1);
	}

	std::pair<float,float> BBox::intersect(const Ray& ray) const
	{
		if (min1.x>max1.x || min1.y>max1.y || min1.z>max1.z)
		{
			std::pair <float,float> intersect;
			intersect = std::make_pair(0,0);
			return intersect;
		}

		double tmin = -FLT_MAX, tmax = FLT_MAX;
 
		  if (ray.d.x != 0.0) {
			double tx1 = (min1.x - ray.o.x)/ray.d.x;
			double tx2 = (max1.x - ray.o.x)/ray.d.x;
 
			tmin = std::max(tmin, std::min(tx1, tx2));
			tmax = std::min(tmax, std::max(tx1, tx2));
		  }
 
		  if (ray.d.y != 0.0) {
			double ty1 = (min1.y - ray.o.y)/ray.d.y;
			double ty2 = (max1.y - ray.o.y)/ray.d.y;
 
			tmin = std::max(tmin, std::min(ty1, ty2));
			tmax = std::min(tmax, std::max(ty1, ty2));
		  }

		    if (ray.d.z != 0.0) {
			double tz1 = (min1.z - ray.o.z)/ray.d.z;
			double tz2 = (max1.z - ray.o.z)/ray.d.z;
 
			tmin = std::max(tmin, std::min(tz1, tz2));
			tmax = std::min(tmax, std::max(tz1, tz2));
		  }
 
			std::pair <float,float> intersect;
			intersect = std::make_pair(tmin,tmax);
			return intersect;
	}

	 bool BBox::isUnbound()
	 {
		 if (min1.x==-FLT_MAX || min1.y==-FLT_MAX || min1.z==-FLT_MAX || max1.x==FLT_MAX || max1.y==FLT_MAX || max1.z==FLT_MAX)
			 return true;
	 }
}