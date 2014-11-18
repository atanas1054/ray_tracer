#include <rt/materials/dummy.h>

namespace rt{

	DummyMaterial::DummyMaterial()
	{

	}

    RGBColor DummyMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
	{

		return RGBColor();
	}

    RGBColor DummyMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return RGBColor(0,0,0);
	}

    Material::SampleReflectance DummyMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return SampleReflectance();
	}

}