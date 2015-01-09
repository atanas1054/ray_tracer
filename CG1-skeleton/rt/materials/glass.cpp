#include <rt/materials/glass.h>
#include <core/random.h>
#include <cmath>
#include <core/scalar.h>
#include <iostream>

namespace rt 
{
	GlassMaterial::GlassMaterial(float eta): eta(eta) { }
    RGBColor GlassMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
	{
		float cosI = dot(normal, outDir);
		float eta2 = eta;
		Vector n = normal;
		if(cosI < 0){
			n = -n;
			eta2 = 1/eta;
			cosI = dot(n, outDir) / n.length() / outDir.length();
		}
		float sinI = std::sqrt(1 - cosI * cosI);
		float sinT = sinI / eta2;
		//
		if(eta2 < 1 && sinT * sinT > 1){
			//total reflection
			Vector r = (2 * dot(outDir, n) * n - outDir).normalize();
			if((outDir - r).length() < epsilon) {
				//compensate the amount by scale to 2?
				RGBColor::rep(2);
			}
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
			Vector r = (2 * dot(outDir, n) * n - outDir).normalize();
			if((r - outDir).length() < epsilon){
			//compensate the amount by scale to 2?
				return RGBColor::rep(R) * 2;
				//return RGBColor::rep(0);
			}
		} else {
			//refract
			Vector i = -outDir;
			Vector t = (i / eta2 + (cosI / eta2 - cosT) * n).normalize();
			if((t - outDir).length() < epsilon){
			//compensate the amount by scale to 2?
				return RGBColor::rep(T) * 2;
				//return RGBColor::rep(0);
			}
		}
	}
    RGBColor GlassMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return RGBColor::rep(0);
	}
    Material::SampleReflectance GlassMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		float cosI = dot(normal, outDir) / normal.length() / outDir.length();
		float eta2 = eta;
		Vector n = normal;
		if(cosI < 0){
			n = -n;
			eta2 = 1/eta;
			cosI = dot(n, outDir) / n.length() / outDir.length();
		}
		float sinI = std::sqrt(1 - cosI * cosI);
		float sinT = sinI / eta2;
		//
		if(eta2 < 1 && sinT * sinT > 1){
			//total reflection
			Vector r = (2 * dot(outDir, n) * n - outDir).normalize();
			//compensate the amount by scale to 2?
			return SampleReflectance(r, RGBColor::rep(2));
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
			Vector r = (2 * dot(outDir, n) * n - outDir).normalize();
			//compensate the amount by scale to 2?
			return SampleReflectance(r, RGBColor::rep(R) * 2);
			//return SampleReflectance(r, RGBColor::rep(0));
		} else {
			//refract
			Vector i = -outDir;
			Vector t = (i / eta2 + (cosI / eta2 - cosT) * n).normalize();
			//compensate the amount by scale to 2?
			return SampleReflectance(t, RGBColor::rep(T) * 2);
			//return SampleReflectance(t, RGBColor::rep(0));
		}
	}
}