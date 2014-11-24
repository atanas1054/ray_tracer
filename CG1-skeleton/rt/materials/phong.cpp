#include <rt/materials/phong.h>


namespace rt{


	PhongMaterial::PhongMaterial(Texture* specular, float exponent)
	{

	}

	RGBColor PhongMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
	{
		return RGBColor();
	}

    RGBColor PhongMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return RGBColor();
	}

    Material::SampleReflectance PhongMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return SampleReflectance();
	}

    Material::Sampling PhongMaterial::useSampling() const
	{
		return Sampling();
	}
}