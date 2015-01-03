#include <rt/materials/fuzzymirror.h>

namespace rt
{
	FuzzyMirrorMaterial::FuzzyMirrorMaterial(float eta, float kappa, float fuzzyangle)
		: eta(eta), kappa(kappa), angle(fuzzyangle) { }
	RGBColor FuzzyMirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
	{
		return RGBColor::rep(0);
	}
    RGBColor FuzzyMirrorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const 
	{
		return RGBColor::rep(0);
	}
    Material::SampleReflectance FuzzyMirrorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const 
	{
		return Material::SampleReflectance::SampleReflectance();
	}
}