#include <rt/bbox.h>
#include <rt/ray.h>
#include <algorithm> 

namespace rt{

	BBox BBox::empty()
	{
		BBox bbox = BBox(Point(0,0,0),Point(0,0,0));
		bbox.isEmpty = true;
		return bbox;
	}

	BBox BBox::full()
	{
		return BBox(Point(FLT_MIN,FLT_MIN,FLT_MIN),Point(FLT_MAX,FLT_MAX,FLT_MAX));
	}

	void BBox::extend(const Point& point)
	{
		if (point.x<min.x) min.x = point.x;
		if (point.y<min.y) min.y = point.y;
		if (point.z<min.z) min.z = point.z;

		if (point.x>max.x) max.x = point.x;
		if (point.y>max.y) max.y = point.y;
		if (point.z>max.z) max.z = point.z;

	}

	void BBox::extend(const BBox& bbox)
	{
		if(isEmpty)
		{
		min=bbox.min;
		max=bbox.max;
		isEmpty = false;
		}
		else
		{
		extend(bbox.min);
		extend(bbox.max);
		
		}
	}

	std::pair<float,float> BBox::intersect(const Ray& ray) const
	{
		if (min.x>max.x || min.y>max.y || min.z>max.z)
		{
			std::pair <float,float> intersect;
			intersect = std::make_pair(0,0);
			return intersect;
		}

		double tmin = -FLT_MAX, tmax = FLT_MAX;
 
		  if (ray.d.x != 0.0) {
			double tx1 = (min.x - ray.o.x)/ray.d.x;
			double tx2 = (max.x - ray.o.x)/ray.d.x;
 
			tmin = std::max(tmin, std::min(tx1, tx2));
			tmax = std::min(tmax, std::max(tx1, tx2));
		  }
 
		  if (ray.d.y != 0.0) {
			double ty1 = (min.y - ray.o.y)/ray.d.y;
			double ty2 = (max.y - ray.o.y)/ray.d.y;
 
			tmin = std::max(tmin, std::min(ty1, ty2));
			tmax = std::min(tmax, std::max(ty1, ty2));
		  }

		    if (ray.d.z != 0.0) {
			double tz1 = (min.z - ray.o.z)/ray.d.z;
			double tz2 = (max.z - ray.o.z)/ray.d.z;
 
			tmin = std::max(tmin, std::min(tz1, tz2));
			tmax = std::min(tmax, std::max(tz1, tz2));
		  }
 
			std::pair <float,float> intersect;
			intersect = std::make_pair(tmin,tmax);
			return intersect;
	}

	 bool BBox::isUnbound()
	 {
		 if (min.x==-FLT_MAX || min.y==-FLT_MAX || min.z==-FLT_MAX || max.x==FLT_MAX || max.y==FLT_MAX || max.z==FLT_MAX)
			 return true;
	 }
}