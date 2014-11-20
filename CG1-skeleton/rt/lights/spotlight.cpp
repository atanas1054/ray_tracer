#include <rt/lights/spotlight.h>
#include <core\color.h>
#include <math.h> 

namespace rt{

	SpotLight::SpotLight(const Point& position, const Vector& direction, float angle, float exp, const RGBColor& intensity)
		: position(position), direction(direction), angle(angle), exp(exp), intensity(intensity)
	{

	}

    LightHit SpotLight::getLightHit(const Point& p) const
	{
		LightHit lh = LightHit();
		lh.direction = position-p;
		lh.distance = lh.direction.length();
		lh.direction = lh.direction.normalize();
		return lh;
	}

    RGBColor SpotLight::getIntensity(const LightHit& irr) const
	{
		if(acos(dot(-irr.direction,direction)/(-irr.direction.length()*direction.length()))<angle)
		{
			return intensity / (pow(1,exp));
		}
		return RGBColor::rep(0);
	}
}