#include <rt/lights/projectivelight.h>
#include <core/scalar.h>
#include <rt/ray.h>
#include <core/julia.h>

namespace rt{

	float a2computeWeight_(float fx, float fy, const Point& c, float div) {
		Point v(fx, fy, 0.0f);
		int numIter = julia(v, c);
		return numIter/(numIter+div);
	}

	RGBColor a2computeColor_(const Ray& r) {
		float theta = asin(r.d.z)/pi*2;
		float phi = atan2(r.d.y,r.d.x)/pi;
		float ofx = absfractional((r.o.x+1.0f)/2.0f)*2.0f-1.0f;
		float ofy = absfractional((r.o.y+1.0f)/2.0f)*2.0f-1.0f;
		RGBColor color = RGBColor::rep(0.0f);
		color = color + a2computeWeight_(phi, theta, Point(-0.8f, 0.156f, 0.0f), 64.0f) * RGBColor(0.8f, 0.8f, 1.0f);
		color = color + a2computeWeight_(phi, theta, Point(-0.6f, 0.2f, 0.0f), 64.0f)*0.2f * RGBColor(0.5f, 0.5f, -0.2f);
		color = color + a2computeWeight_(ofy, ofx, Point(0.285f, 0.0f, 0.0f), 64.0f) * RGBColor(0.4f, 0.5f, 0.6f);
		color = RGBColor::rep(1.0f) - color;
		if (absfractional(theta/(2*pi)*90)<0.03) color = RGBColor(0.9f,0.5f,0.5f)*0.7f;
		if (absfractional(phi/(2*pi)*90)<0.03) color = RGBColor(0.9f,0.9f,0.5f)*0.7f;
		return color;
	}

	ProjectiveLight::ProjectiveLight(const Point& position, const RGBColor& intensity):
		position(position), intensity(intensity) { }

	LightHit ProjectiveLight::getLightHit(const Point& p) const
	{
		LightHit lh = LightHit();
		lh.direction = position - p;
		lh.distance = lh.direction.length();
		lh.direction = lh.direction.normalize();
		return lh;
	}

    RGBColor ProjectiveLight::getIntensity(const LightHit& irr) const
	{
		return /*a2computeColor_(Ray(position, irr.direction)) **/ intensity / irr.distance / irr.distance;
	}
}