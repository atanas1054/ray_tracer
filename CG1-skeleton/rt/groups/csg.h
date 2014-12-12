#ifndef CG1RAYTRACER_GROUPS_CSG_HEADER
#define CG1RAYTRACER_GROUPS_CSG_HEADER

#include <rt/groups/group.h>
#include <rt/solids/solid.h>
#include <vector>

namespace rt {



	class CSG : public Solid {
		public:
			enum CombineType {
				UNION,
				DIFFERENCE,
				INTERSECT
			};
			std::vector<CSG*> csgs;
			CombineType combyneType;
			Point center;
			BBox bbox;

			CSG(CombineType ct) : Solid(nullptr,  nullptr), combyneType(ct) { }
			CSG(CombineType ct, CoordMapper* cm, Material* m) : Solid(cm,  m), combyneType(ct) { }
			CSG(CombineType ct, CSG* a, CSG* b, CoordMapper* cm, Material* m);
			virtual Point getCenter() const;
			virtual BBox getBounds() const;
			virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
			virtual std::vector<Intersection*> intersections(const Ray& ray) const;
			virtual void setMaterial(Material* m);
			virtual void setCoordMapper(CoordMapper* cm);
			virtual void add(CSG* csg);
			virtual Point sample() const;
			virtual float getArea() const;
	};

}

#endif
