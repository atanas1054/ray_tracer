#include <rt/materials/mirror.h>

namespace rt{

	MirrorMaterial::MirrorMaterial(float eta, float kappa)
	{

	}

	RGBColor MirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
	{
		return RGBColor();
	}

    RGBColor MirrorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return RGBColor();
	}

    Material::SampleReflectance MirrorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return SampleReflectance();
	}

    Material::Sampling MirrorMaterial::useSampling() const
	{
		return Sampling();
	}
}