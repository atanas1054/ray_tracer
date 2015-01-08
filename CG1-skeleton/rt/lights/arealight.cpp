#include <rt/lights/arealight.h>
#include <core/color.h>
#include <rt/materials/material.h>

namespace rt 
{
	AreaLight::AreaLight(Solid* source): solid(source) { }
	LightHit AreaLight::getLightHit(const Point& p) const 
	{
		LightHit lh = LightHit();
		Point position = solid->sample();
		lh.direction = position - p;
		lh.distance = lh.direction.length();
		lh.direction = lh.direction.normalize();
		return lh;
	}
	RGBColor AreaLight::getIntensity(const LightHit& irr) const
	{
		//currently set to dummy values
		RGBColor c = solid->material->getEmission(Point::rep(0), Vector::rep(0), Vector::rep(0)) / (irr.distance * irr.distance) * solid->getArea();
		return c;
	}
}