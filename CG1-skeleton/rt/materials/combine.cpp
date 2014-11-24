#include <rt/materials/combine.h>

namespace rt{

	CombineMaterial::CombineMaterial()
	{

	}

    void CombineMaterial::add(Material* material, float weight)
	{

	}

    RGBColor CombineMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
	{
		return RGBColor();
	}

    RGBColor CombineMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return RGBColor();
	}

    Material::SampleReflectance CombineMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return SampleReflectance();
	}

    Material::Sampling CombineMaterial::useSampling() const
	{
		return Sampling();
	}
}