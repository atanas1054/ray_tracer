#include <rt/integrators/raytrace.h>
#include <core/color.h>
#include <rt/world.h>
#include <rt/lights/light.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>


namespace rt{

	RGBColor RayTracingIntegrator::getRadiance(const Ray& ray) const
	{
		Intersection intersect  = world->scene->intersect(ray);
		if(intersect)
		{
			RGBColor color = intersect.solid->material->getEmission(intersect.local(), intersect.normal(), -ray.d);
			Point p = ray.getPoint(intersect.distance-0.00001);
			
			for(int i = 0; i < world->light.size();i++)
			{
				LightHit lh = world->light[i]->getLightHit(p);

				float n1 = dot(ray.o-p, intersect.normal());
				float n2 = dot(lh.direction, intersect.normal());
				if((n1 > 0 && n2 > 0) || (n1 < 0 && n2 < 0))
				{
					Ray shadowRay = Ray(p, lh.direction);
					Intersection shadowIntrsct = world->scene->intersect(shadowRay, lh.distance);
					if(!shadowIntrsct)
					{
						RGBColor sourceColor = world->light[i]->getIntensity(lh);
						RGBColor reflectInt = intersect.solid->material->getReflectance(intersect.local(), intersect.normal(), -ray.d, -lh.direction);
						RGBColor reflectColor = sourceColor * reflectInt;
						color = color + reflectColor;
					}
				}
			}
			return color;
		}
		return RGBColor::rep(0);
	}
}