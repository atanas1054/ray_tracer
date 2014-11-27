#include <rt/materials/mirror.h>

namespace rt{

	MirrorMaterial::MirrorMaterial(float eta, float kappa): eta(eta), kappa(kappa) { }

	//
	RGBColor MirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
	{
		Vector Ri = -(inDir - (2 * dot(normal, inDir) * normal)).normalize();
		if((outDir + Ri).length() < 0.000001)
			return RGBColor::rep(1 - kappa);
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