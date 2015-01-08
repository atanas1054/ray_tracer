#include <rt/materials/glass.h>
#include <core/random.h>
#include <cmath>

namespace rt 
{
	GlassMaterial::GlassMaterial(float eta): eta(eta) { }
    RGBColor GlassMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
	{
		return RGBColor::rep(0);
	}
    RGBColor GlassMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return RGBColor::rep(0);
	}
    Material::SampleReflectance GlassMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		float cosI = dot(normal, outDir);
		float sinI = std::sqrt(1 - cosI * cosI);
		float eta2 = eta;
		if(cosI < 0){
			cosI = -cosI;
			eta2 = 1/eta;
		}
		float sinT = sinI / eta2;
		//
		if(eta2 < 1 && sinT * sinT > 1){
			//total reflection
			Vector r = (2 * dot(outDir, normal) * normal - outDir).normalize();
			return SampleReflectance(r, RGBColor::rep(1));
		}
		//
		float cosT = std::sqrt(1 - sinT * sinT);
		//assume eta1 = 1
		float Rr = (cosI - eta2 * cosT) / (cosI + eta2 * cosT);
		Rr = Rr * Rr;
		float Rp = (eta2 * cosI - cosT) / (eta2 * cosI + cosT);
		Rp = Rp * Rp;
		//
		float R = (Rr + Rp) / 2;
		float T = 1 - R;
		//
		if(random() < 0.5){
			//reflect
			Vector r = (2 * dot(outDir, normal) * normal - outDir).normalize();
			//compensate the amount by scale to 2?
			return SampleReflectance(r, RGBColor::rep(R) * 2);
		} else {
			//refract
			Vector i = -outDir;
			Vector t = i / eta2 + (cosI / eta2 - cosT) * normal;
			//compensate the amount by scale to 2?
			return SampleReflectance(t, RGBColor::rep(T) * 2);
		}
	}
}