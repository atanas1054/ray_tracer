#include <rt/solids/solid.h>
#include <rt/coordmappers/worldmapper.h>
#include <rt/coordmappers/coordmapper.h>

namespace rt 
{
	Solid::Solid(CoordMapper* texMapper, Material* material) 
		: texMapper(texMapper), material(material) {
			if(Solid::texMapper == nullptr)
			{
				Solid::texMapper = new WorldMapper();
			}
	}
}