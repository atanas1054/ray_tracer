#include <rt/lights/light.h>
#include <core/color.h>

namespace rt 
{
	LightHit Light::getLightHit(const Point& p) const
	{
		return LightHit();
	}

	RGBColor Light::getIntensity(const LightHit& irr) const
	{
		return RGBColor::rep(0);
	}
}