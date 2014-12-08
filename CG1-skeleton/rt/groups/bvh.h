#ifndef CG1RAYTRACER_GROUPS_BVH_HEADER
#define CG1RAYTRACER_GROUPS_BVH_HEADER

#include <vector>
#include <rt/groups/group.h>
#include <rt/bbox.h>

namespace rt {

class BVH : public Group {
public:
	struct Node {
	  BBox bbox;
	  Node* leftChild;
	  Node* rightChild;
	  std::vector<Primitive*> objectList;
	};

	Node* root;

	BVH(){
	};
	virtual Point getCenter() const;
    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
    virtual void rebuildIndex();
	virtual ~BVH(){
	};
    virtual void add(Primitive* p);
	void BuildBVH(Node* &node, std::vector<Primitive*> listOfObjects);
	void BuildBVH2(Node* &node, std::vector<Primitive*> listOfObjects);
	void BuildBVHwithSAH(Node* &node, std::vector<Primitive*> listOfObjects);
    virtual void setMaterial(Material* m);
    virtual void setCoordMapper(CoordMapper* cm);

	std::vector<Primitive*> primitives;

private:
	void SplitObjByAxisValue(std::vector<Primitive*> &listObj, int axisCode, float splitVal, std::vector<Primitive*> &leftObj, std::vector<Primitive*> &rightObj);
	void SplitObjByAxisSorting(std::vector<Primitive*> &listObj, int axisCode, std::vector<Primitive*> &leftObj, std::vector<Primitive*> &rightObj);
	Intersection IntersectNode(const Node& n, const Ray& ray, float bestDist) const;
	//range min and max is [0,1]
	std::pair <float,float> findSAHSplitValue(std::vector<Primitive*> &listOfObjects, BBox &bbox, int axis, float rangeMin , float rangeMax);
	float calcCost(std::vector<Primitive*> &listOfObjects, BBox &bbox,float splitValue,int axis);
	float calcBBoxArea(BBox &bbox);
};

}

#endif
