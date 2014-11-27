#include <rt/materials/combine.h>

namespace rt{

	CombineMaterial::CombineMaterial()
	{

	}

    void CombineMaterial::add(Material* material, float weight)
	{
		std::pair <Material*,float> materialPair;
		materialPair.first = material;
		materialPair.second = weight;
		materials.push_back(materialPair);

		bool sampling_secondary = false;

		for(int i=0;i<materials.size();i++)
		{
			if (materials.at(i).first->useSampling() == Material::SAMPLING_ALL)
			{
				sampling = SAMPLING_ALL;
				return;
			}
			else if(materials.at(i).first->useSampling() == Material::SAMPLING_SECONDARY)
			{
				sampling_secondary=true;
			}

				
		}
		if(sampling_secondary)
			sampling = SAMPLING_SECONDARY;
		else
			sampling = SAMPLING_NOT_NEEDED;
	}

    RGBColor CombineMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
	{
		RGBColor color = RGBColor::rep(0);
		for(int i=0;i<materials.size();i++)
		{
			color = color + materials.at(i).first->getReflectance(texPoint,normal,outDir,inDir)*materials.at(i).second;
		}
		return color;
	}

    RGBColor CombineMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		RGBColor color = RGBColor::rep(0);
		for(int i=0;i<materials.size();i++)
		{
			color = color + materials.at(i).first->getEmission(texPoint,normal,outDir)*materials.at(i).second;
		}
		return color;
	}

    Material::SampleReflectance CombineMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
	{
		Vector Rv = -(outDir - 2 * dot(outDir, normal) * normal).normalize();
		return SampleReflectance(Rv, getReflectance(texPoint, normal, outDir, -Rv)); 
	}

    Material::Sampling CombineMaterial::useSampling() const
	{
		return sampling;
	}
}