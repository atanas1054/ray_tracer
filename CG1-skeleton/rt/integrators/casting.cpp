#include <rt/integrators/casting.h>
#include <core/color.h>
#include <rt/ray.h>
#include <rt/world.h>

namespace rt
{
	RGBColor RayCastingIntegrator::getRadiance(const Ray& ray) const 
	{
		World *world = RayCastingIntegrator::world;
		Intersection intersect = (*(*world).scene).intersect(ray);
		if(intersect)
		{
			float cos = dot(-ray.d, intersect.normal()) / (ray.d.length() * intersect.normal().length());
			return RGBColor(cos, cos, cos);
		}
		return RGBColor(0,0,0);
	}
}