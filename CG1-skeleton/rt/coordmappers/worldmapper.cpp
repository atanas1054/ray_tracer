#include <rt/coordmappers/worldmapper.h>
#include <core/float4.h>
#include <core/point.h>

namespace rt {
	WorldMapper::WorldMapper()
	{
		scale = Float4::rep(1);
	}
	WorldMapper::WorldMapper(const Float4& scale) : scale(scale)
	{
	}
	Point WorldMapper::getCoords(const Intersection& hit) const 
	{
		Point p = hit.hitPoint();
		return Point(scale.x * p.x, scale.y * p.y, scale.z * p.z);
	}
}