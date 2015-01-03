#include <rt/materials/glass.h>

namespace rt 
{
	GlassMaterial::GlassMaterial(float eta): eta(eta) { }
    RGBColor GlassMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
	{
		return RGBColor::rep(0);
	}
    RGBColor GlassMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return RGBColor::rep(0);
	}
    Material::SampleReflectance GlassMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return Material::SampleReflectance::SampleReflectance();
	}
}