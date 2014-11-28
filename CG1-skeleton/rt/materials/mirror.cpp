#include <rt/materials/mirror.h>
#include <core/scalar.h>

namespace rt{

	MirrorMaterial::MirrorMaterial(float eta, float kappa): eta(eta), kappa(kappa) { }

	//
	RGBColor MirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
	{
		//cos I-P = sin I-N
		float cosIP = cross(-inDir, normal).length() / inDir.length() / normal.length();
		float cosOP = cross(outDir, normal).length() / outDir.length() / normal.length();
		float cosOPsqr = cosOP * cosOP;
		float eta2cosOP = 2 * eta * cosOP;
		float eta2kappa2 = (eta * eta + kappa * kappa);
		float rp = (eta2kappa2 * cosOPsqr - eta2cosOP + 1) / (eta2kappa2 * cosOPsqr + eta2cosOP + 1);
		float rs = (eta2kappa2 - eta2cosOP + cosOPsqr) / (eta2kappa2 + eta2cosOP + cosOPsqr); 
		float fr = (rp + rs) / 2;
		Vector Ri = ((2 * dot(normal, -inDir) * normal) - (-inDir)).normalize();
		if((outDir - Ri).length() < 0.000001)
			//return RGBColor::rep(fr) / cosIP;
			return RGBColor::rep(fr);
		else 
			return RGBColor::rep(0);
	}

    RGBColor MirrorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return RGBColor::rep(0);
	}

    Material::SampleReflectance MirrorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		Vector Rv = -(outDir - 2 * dot(outDir, normal) * normal).normalize();
		return SampleReflectance(Rv, getReflectance(texPoint, normal, outDir, -Rv)); 
	}

    Material::Sampling MirrorMaterial::useSampling() const
	{
		return SAMPLING_ALL;
	}
}