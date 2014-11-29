#include <rt/materials/lambertian.h>
#include <core/scalar.h>

namespace rt{

	LambertianMaterial::LambertianMaterial(Texture* emission, Texture* diffuse): emission(emission), diffuse(diffuse)
	{

	}

	RGBColor LambertianMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
	{
		return (dot(normal, inDir) * diffuse->getColor(texPoint)) / pi;
	}

    RGBColor LambertianMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return emission->getColor(texPoint);
	}

    Material::SampleReflectance LambertianMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return SampleReflectance(normal, RGBColor::rep(0));
	}

    Material::Sampling LambertianMaterial::useSampling() const
	{
		return Material::Sampling::SAMPLING_NOT_NEEDED;
	}
}