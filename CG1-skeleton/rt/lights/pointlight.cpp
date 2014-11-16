#include <rt/lights/pointlight.h>

namespace rt{

	PointLight::PointLight(const Point& position, const RGBColor& intensity)
	{

	}

	LightHit PointLight::getLightHit(const Point& p) const
	{
		return LightHit();
	}

    RGBColor PointLight::getIntensity(const LightHit& irr) const
	{
		return RGBColor();
	}
}