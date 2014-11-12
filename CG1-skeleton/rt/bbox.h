#ifndef CG1RAYTRACER_BBOX_HEADER
#define CG1RAYTRACER_BBOX_HEADER

#include <utility>
#include <core/point.h>
#include <core/vector.h>

namespace rt {

class Ray;

class BBox {
public:
    Point min1, max1;

    BBox() {}
    BBox(const Point& min, const Point& max) : min1(min), max1(max) {}
    static BBox empty();
    static BBox full();

    void extend(const Point& point);
    void extend(const BBox& bbox);

    Vector diagonal() const { return max1 - min1; }

    std::pair<float,float> intersect(const Ray& ray) const;

    bool isUnbound();
};

}


#endif
