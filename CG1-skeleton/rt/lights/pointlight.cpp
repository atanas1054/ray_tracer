#include <rt/lights/pointlight.h>

namespace rt{

	PointLight::PointLight(const Point& position, const RGBColor& intensity):
		position(position), intensity(intensity) { }

	LightHit PointLight::getLightHit(const Point& p) const
	{
		LightHit lh = LightHit();
		lh.direction = position-p;
		lh.distance = lh.direction.length();
		lh.direction = lh.direction.normalize();
		return lh;
	}

    RGBColor PointLight::getIntensity(const LightHit& irr) const
	{
		return intensity / (irr.distance * irr.distance);
	}
}