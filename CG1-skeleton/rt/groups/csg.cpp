#include <rt/groups/csg.h>

namespace rt 
{

	CSG::CSG(CombineType ct, CSG* a, CSG* b, CoordMapper* cm, Material* m)
		: Solid(nullptr, nullptr), combyneType(ct)
	{
		setMaterial(m);
		setCoordMapper(cm);
		add(a);
		add(b);
	}

	Point CSG::getCenter() const {
		return center;
	}

	BBox CSG::getBounds() const {
		return bbox;
	}

	Intersection CSG::intersect(const Ray& ray, float previousBestDistance) const {
		std::vector<Intersection*> intersections = CSG::intersections(ray);
		if(intersections.size() > 0 && intersections[0]->distance < previousBestDistance){
			int index = 0;
			while(index < intersections.size() && intersections[index]->distance < 0){
				index++;
			}
			if(index < intersections.size()){
				Intersection i = Intersection(
					intersections[index]->distance, ray,
					intersections[index]->solid, 
					intersections[index]->normal(), 
					intersections[index]->local());
				return i;
			}
		}
		return Intersection::failure();
	}
	
	std::vector<Intersection*> CSG::intersections(const Ray& ray) const {
		std::vector<Intersection*> result;
		if(combyneType == CombineType::UNION){
			for(int i = 0 ; i < csgs.size(); i++)
			{
				std::vector<Intersection*> single = csgs[i]->intersections(ray);
				if(result.size() == 0 && single.size() > 0)
				{
					result = single;
				} else if(result.size() > 0 && single.size() > 0){
					int indexA = 0;
					int indexB = 0;
					bool insideA = false;
					bool insideB = false;
					bool insideR = false;
					std::vector<Intersection*> intrs;
					while(indexA < result.size() || indexB < single.size())
					{
						if(indexA == result.size()) {
							insideB = !insideB;
							if(insideB && !insideR){
								insideR = !insideR;
								intrs.push_back(single[indexB]);
							}else if(!insideB && insideR){
								insideR = !insideR;
								intrs.push_back(single[indexB]);
							}
							indexB++;
						}else if(indexB == single.size()){
							insideA = !insideA;
							if(insideA && !insideR){
								insideR = !insideR;
								intrs.push_back(result[indexA]);
							}else if(!insideA && insideR){
								insideR = !insideR;
								intrs.push_back(result[indexA]);
							}
							indexA++;
						}
						else if(result[indexA]->distance < single[indexB]->distance)
						{
							insideA = !insideA;
							if(insideA && !insideR) {
								insideR = !insideR;
								intrs.push_back(result[indexA]);
							} else if(!insideA && !insideB && insideR) {
								insideR = !insideR;
								intrs.push_back(result[indexA]);
							}
							indexA++;
						} else {
							insideB = !insideB;
							if(insideB && !insideR) {
								insideR = !insideR;
								intrs.push_back(single[indexB]);
							} else if(!insideA && !insideB && insideR) {
								insideR = !insideR;
								intrs.push_back(single[indexB]);
							}
							indexB++;
						}
					}
					result = intrs;
				}
			}
		}
		else if(combyneType == CombineType::INTERSECT){
			bool intersecting = false;
			for(int i = 0 ; i < csgs.size(); i++)
			{
				std::vector<Intersection*> single = csgs[i]->intersections(ray);
				if(result.size() == 0 && single.size() > 0)
				{
					result = single;
				} else if(result.size() > 0 && single.size() > 0){
					intersecting = true;
					int indexA = 0;
					int indexB = 0;
					bool insideA = false;
					bool insideB = false;
					bool insideR = false;
					std::vector<Intersection*> intrs;
					while(indexA < result.size() && indexB < single.size())
					{
						if(result[indexA]->distance < single[indexB]->distance)
						{
							insideA = !insideA;
							if(!insideA && insideR) {
								insideR = !insideR;
								intrs.push_back(result[indexA]);
							} else if(insideA && insideB && !insideR) {
								insideR = !insideR;
								intrs.push_back(result[indexA]);
							}
							indexA++;
						} else {
							insideB = !insideB;
							if(!insideB && insideR) {
								insideR = !insideR;
								intrs.push_back(single[indexB]);
							} else if(insideA && insideB && !insideR) {
								insideR = !insideR;
								intrs.push_back(single[indexB]);
							}
							indexB++;
						}
					}
					result = intrs;
				}
			}
			if(!intersecting){
				result.clear();
			}
		}
		else {
			result = csgs[0]->intersections(ray);
			if(result.size() > 0){
				for(int i = 1 ; i < csgs.size(); i++)
				{
					std::vector<Intersection*> single = csgs[i]->intersections(ray);
					if(single.size() > 0){
						int indexA = 0;
						int indexB = 0;
						bool insideA = false;
						bool insideB = false;
						std::vector<Intersection*> intrs;
						while(indexA < result.size())
						{
							if(indexB == single.size()){
								insideA = !insideA;
								intrs.push_back(result[indexA]);
								indexA++;
							} 
							else if(result[indexA]->distance < single[indexB]->distance)
							{
								insideA = !insideA;
								if(insideA && !insideB) {
									intrs.push_back(result[indexA]);
								} else if(!insideA) {
									intrs.push_back(result[indexA]);
								}
								indexA++;
							} else {
								insideB = !insideB;
								if(insideA && !insideB) {
									intrs.push_back(single[indexB]);
								} else if(insideB && insideA) {
									intrs.push_back(single[indexB]);
								}
								indexB++;
							}
						}
						result = intrs;
					}
				}
			}
		}
		return result;
	}
	
	void CSG::setMaterial(Material* m) {
		for(int i = 0; i < csgs.size(); i++)
		{
			csgs[i]->setMaterial(m);
		}
	}

	void CSG::setCoordMapper(CoordMapper* cm) {
		for(int i = 0; i < csgs.size(); i++)
		{
			csgs[i]->setCoordMapper(cm);
		}
	}

	void CSG::add(CSG* csg) { 
		csgs.push_back(csg);
	}

	Point CSG::sample() const 
	{
		return Point::rep(0);
	}
	float CSG::getArea() const
	{
		return 0;
	}

}