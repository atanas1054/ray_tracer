#include <rt/materials/flatmaterial.h>

namespace rt{

	FlatMaterial::FlatMaterial(Texture* texture)
	{

	}

    RGBColor FlatMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
	{
		return RGBColor();
	}

    RGBColor FlatMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return RGBColor();
	}

     Material::SampleReflectance FlatMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return Material::SampleReflectance();
	}

}