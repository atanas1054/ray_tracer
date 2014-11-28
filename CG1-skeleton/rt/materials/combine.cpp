#include <rt/materials/combine.h>

namespace rt{

	CombineMaterial::CombineMaterial()
	{

	}

    void CombineMaterial::add(Material* material, float weight)
	{
		std::pair <Material*,float> materialPair = std::make_pair(material, weight);
		materials.push_back(materialPair);

		bool sampling_secondary = false;
		int usesample = 0;
		int nosample = 0;
		for(int i=0;i<materials.size();i++)
		{
			if (materials.at(i).first->useSampling() == Material::SAMPLING_ALL)
			{
				usesample++;
			}
			else if(materials.at(i).first->useSampling() == Material::SAMPLING_NOT_NEEDED)
			{
				nosample++;
			}	
		}
		if(usesample > 0 && nosample > 0)
			sampling = SAMPLING_SECONDARY;
		else if(usesample > 0)
			sampling = SAMPLING_ALL;
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
		Vector Rv = (2 * dot(outDir, normal) * normal - outDir).normalize();
		return SampleReflectance(Rv, getReflectance(texPoint, normal, outDir, -Rv)); 
	}

    Material::Sampling CombineMaterial::useSampling() const
	{
		return sampling;
	}
}