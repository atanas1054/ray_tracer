#include <rt/integrators/castingdist.h>
#include <core/color.h>
#include <rt/ray.h>
#include <rt/intersection.h>
#include <rt/world.h>

namespace rt 
{
	RayCastingDistIntegrator::RayCastingDistIntegrator(World* world, const RGBColor& nearColor, float nearDist, const RGBColor& farColor, float farDist)
		:Integrator(world), nearDist(nearDist),  nearColor(nearColor)
	{
		lenDist = farDist - nearDist;
		lenR = farColor.r - nearColor.r;
		lenG = farColor.g - nearColor.g;
		lenB = farColor.b - nearColor.b;
	}
    
	RGBColor RayCastingDistIntegrator::getRadiance(const Ray& ray) const
	{
		World *world = RayCastingDistIntegrator::world;
		Intersection intersect = (*(*world).scene).intersect(ray);
		if(intersect)
		{
			float scale = (( intersect.distance - nearDist) / lenDist);
			RGBColor newColor(
				nearColor.r + scale * lenR, 
				nearColor.g + scale * lenG,
				nearColor.b + scale * lenB
			);
			newColor = newColor.clamp();
			float cos = dot(-ray.d, intersect.normal()) / (ray.d.length() * intersect.normal().length());
			newColor = newColor * cos;
			return newColor;
		}
		return RGBColor(0,0,0);
	}
}