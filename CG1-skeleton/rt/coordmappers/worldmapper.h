#ifndef CG1RAYTRACER_COORDMAPPERS_WORLD_HEADER
#define CG1RAYTRACER_COORDMAPPERS_WORLD_HEADER

#include <core/vector.h>
#include <rt/coordmappers/coordmapper.h>
#include <rt/intersection.h>
#include <core/float4.h>

namespace rt {

class WorldMapper : public CoordMapper {
public:
	Float4 scale;
    WorldMapper();
	//explicit keyword removed
    WorldMapper(const Float4& scale);
    virtual Point getCoords(const Intersection& hit) const;
};

}

#endif