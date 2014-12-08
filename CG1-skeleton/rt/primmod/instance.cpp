#include <rt/primmod/instance.h>

namespace rt{

	Instance::Instance(Primitive* content): content_(content)
	{

	}
	
	Primitive* Instance::content()
	{
		return content_;
	}

	Point Instance::getCenter() const
	{
		return Point();
	}

    BBox  Instance::getBounds() const
	{
		return BBox();
	}

    Intersection  Instance::intersect(const Ray& ray, float previousBestDistance) const
	{
		return Intersection();
	}

    void  Instance::setMaterial(Material* m)
	{

	}

    void  Instance::setCoordMapper(CoordMapper* cm)
	{

	}

	//reset transformation back to identity
	void Instance::reset()
	{

	}

    void Instance::translate(const Vector& t)
	{

	}

    void Instance::rotate(const Vector& axis, float angle)
	{

	}

    void Instance::scale(float scale)
	{

	}

    void Instance::scale(const Vector& scale)
	{

	}

}