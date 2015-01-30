#include <rt/integrators/recraytrace.h>
#include <core/color.h>
#include <rt/world.h>
#include <rt/lights/light.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>
#include <rt/intersection.h>
#include <rt/coordmappers/tmapper.h>

namespace rt{

	RGBColor RecursiveRayTracingIntegrator::getRadiance(const Ray& ray) const
	{
		return getRadianceRec(ray, 0);
	}

	RGBColor RecursiveRayTracingIntegrator::getRadianceRec(const Ray& ray, int counter) const
	{
		if(counter > 6)
		{
			return RGBColor::rep(0);
		}
		Intersection intersect  = world->scene->intersect(ray);
		if(intersect)
		{
			RGBColor color = RGBColor::rep(0.1f) + intersect.solid->material->getEmission(
				intersect.solid->texMapper->getCoords(intersect),
				intersect.normal(), -ray.d);
			Point p = intersect.hitPoint();
			if(intersect.solid->material->useSampling() == Material::Sampling::SAMPLING_NOT_NEEDED)
			{			
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
							RGBColor reflectInt = intersect.solid->material->getReflectance(intersect.solid->texMapper->getCoords(intersect), intersect.normal(), -ray.d, lh.direction);
							RGBColor reflectColor = sourceColor * reflectInt;
							color = color + reflectColor;
							//color = color + reflectInt;
						}
					}
				}
			}
			else if(intersect.solid->material->useSampling() == Material::Sampling::SAMPLING_ALL)
			{
				Material::SampleReflectance sample = intersect.solid->material->getSampleReflectance(intersect.solid->texMapper->getCoords(intersect), intersect.normal(), -ray.d);
				RGBColor refColor = getRadianceRec(Ray(p, sample.direction), counter + 1);
				color = color + (refColor * sample.reflectance);
			}
			else if(intersect.solid->material->useSampling() == Material::Sampling::SAMPLING_SECONDARY)
			{
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
							RGBColor reflectInt = intersect.solid->material->getReflectance(intersect.solid->texMapper->getCoords(intersect), intersect.normal(), -ray.d, -lh.direction);
							RGBColor reflectColor = sourceColor * reflectInt;
							color = color + reflectColor;
						}
					}
				}
				Material::SampleReflectance sample = intersect.solid->material->getSampleReflectance(intersect.solid->texMapper->getCoords(intersect), intersect.normal(), -ray.d);
				RGBColor refColor = getRadianceRec(Ray(intersect.hitPoint(), sample.direction), counter + 1);
				color = color + (refColor * sample.reflectance);
			}
			return color;
		}
		return RGBColor::rep(0);
	}
}