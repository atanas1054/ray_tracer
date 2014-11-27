#include <rt/materials/phong.h>
#include <rt/textures/texture.h>
#include <cmath>
#include <core/scalar.h>

namespace rt{


	PhongMaterial::PhongMaterial(Texture* specular, float exponent): tex(specular), exp(exponent) { }

	//outDir the direction from hit point to viewer
	//inDir the direction from light source to hit point
	RGBColor PhongMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
	{
		RGBColor color = tex->getColor(texPoint);
		Vector Ri = -(inDir - 2 * dot(inDir, normal) * normal).normalize();
		float cos = dot(Ri, outDir) / outDir.length() / Ri.length();
		return color * std::powf(cos, exp);// * (exp + 2) / 2 / pi;
	}

    RGBColor PhongMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		return RGBColor::rep(0);
	}

	//outDir the direction from hit point to viewer
    Material::SampleReflectance PhongMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		Vector Rv = -(outDir - 2 * dot(outDir, normal) * normal).normalize();
		return SampleReflectance(Rv, PhongMaterial::getReflectance(texPoint, normal, outDir, -Rv)); 
	}

    Material::Sampling PhongMaterial::useSampling() const
	{
		return Sampling::SAMPLING_NOT_NEEDED;
	}
}