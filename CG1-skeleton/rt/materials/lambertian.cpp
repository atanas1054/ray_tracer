#include <rt/materials/lambertian.h>

namespace rt{

	LambertianMaterial::LambertianMaterial(Texture* emission, Texture* diffuse)
	{

	}

	RGBColor LambertianMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
	{
		return RGBColor();
	}

    RGBColor LambertianMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return RGBColor();
	}

    Material::SampleReflectance LambertianMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return SampleReflectance();
	}

    Material::Sampling LambertianMaterial::useSampling() const
	{
		return Sampling();
	}
}