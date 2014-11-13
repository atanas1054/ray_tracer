#include <rt/groups/simplegroup.h>
#include <rt/intersection.h>
#include <fstream>
#include <iostream>
namespace rt {

	Intersection SimpleGroup::intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const {
		Intersection intersect;
		Intersection bestIntersect = Intersection::failure();
		float bestDist = previousBestDistance;
		
		for(int i = 0;i < primitives.size(); i++)
		{
			intersect = (*primitives[i]).intersect(ray, bestDist);
			if(intersect)
			{
				bestIntersect = intersect;
				bestDist = bestIntersect.distance;
			}
		}
		return bestIntersect;
	}
	void SimpleGroup::rebuildIndex() {
	}
    void SimpleGroup::add(Primitive* p) {
		primitives.push_back(p);
	}

	BBox SimpleGroup::getBounds() const
	{
		BBox bbox = BBox::empty();

		for(int i = 0;i < primitives.size(); i++)
		{
			bbox.extend((*primitives[i]).getBounds());
			//bbox = (*primitives[i]).getBounds();
		}

		return bbox;

	}

}