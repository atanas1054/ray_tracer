#include <rt/solids/solid.h>
#include <rt/coordmappers/world.h>

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