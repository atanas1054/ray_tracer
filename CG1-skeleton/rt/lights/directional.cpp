#include <rt/lights/directional.h>
#include <core\assert.h>

namespace rt{


	DirectionalLight::DirectionalLight(const Vector& direction, const RGBColor& color)
	:
	direction(direction), color(color) { }

	LightHit DirectionalLight::getLightHit(const Point& p) const
	{
		LightHit lh = LightHit();
		lh.direction = -direction;
		lh.distance = FLT_MAX;
		return lh;
	}

	RGBColor DirectionalLight::getIntensity(const LightHit& irr) const
	{
		return color;
	}
}