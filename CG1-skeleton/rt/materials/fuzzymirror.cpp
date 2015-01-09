#include <rt/materials/fuzzymirror.h>
#include <core/scalar.h>
#include <cmath>
#include <core/random.h>

namespace rt
{
	FuzzyMirrorMaterial::FuzzyMirrorMaterial(float eta, float kappa, float fuzzyangle)
		: eta(eta), kappa(kappa), angle(fuzzyangle) { }
	RGBColor FuzzyMirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
	{
		//cos I-P = sin I-N
		float cosIP = cross(inDir, normal).length() / inDir.length() / normal.length();
		float cosIPsqr = cosIP * cosIP;
		float eta2cosIP = 2 * eta * cosIP;
		float eta2kappa2 = (eta * eta + kappa * kappa);
		float rp = (eta2kappa2 * cosIPsqr - eta2cosIP + 1) / (eta2kappa2 * cosIPsqr + eta2cosIP + 1);
		float rs = (eta2kappa2 - eta2cosIP + cosIPsqr) / (eta2kappa2 + eta2cosIP + cosIPsqr); 
		float fr = (rp + rs) / 2;
		Vector Ri = ((2 * dot(normal, inDir) * normal) - (inDir)).normalize();
		if(dot(normal, Ri) > 0 && dot(Ri, outDir) > std::cos(angle))
			return RGBColor::rep(fr);
		else 
			return RGBColor::rep(0);
	}
    RGBColor FuzzyMirrorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const 
	{
		return RGBColor::rep(0);
	}
    Material::SampleReflectance FuzzyMirrorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const 
	{
		float u = random();
		float v = std::sqrt(random());
		float theta = u * 2 * pi;
		float dx = std::cos(theta) * v;
		float dy = std::sin(theta) * v;

		Vector z = (2 * dot(outDir, normal) * normal - outDir).normalize();
		Vector y = cross(normal, z).normalize();
		y = y * std::tan(angle);
		Vector x = cross(y, z).normalize() * y.length();
		Vector res = (z + dx * x + dy * y).normalize();
		RGBColor c = getReflectance(texPoint, normal, outDir, res);
		return SampleReflectance(res, c); 
	}
}