#include <rt/groups/bvh.h>
#include <iostream>
namespace rt {



	void BVH::add(Primitive* p)
	{
		primitives.push_back(p);
	}

	Intersection BVH::intersect(const Ray& ray, float previousBestDistance) const
	{
		return Intersection();
	}

	BBox BVH::getBounds() const
	{

		return BBox::empty();
	}

	void BVH::rebuildIndex()
	{
		BuildBVH(root,primitives);
	}

	void BVH::BuildBVH(Node* node, std::vector<Primitive*> listOfObjects)
	{
		BBox bbox = BBox::empty();
		for(int i = 0;i < listOfObjects.size(); i++)
		{
			bbox.extend((*listOfObjects[i]).getBounds());
		}

		
		node->bbox = bbox;

		if(listOfObjects.size()<3)
		{
			node->objectList = listOfObjects;
			return;
		}

		 std::vector<Primitive*> leftObjects;
		 std::vector<Primitive*> rightObjects;
		 
		 float splittingValue;
		 int splittingAxis;
		 //x is the longest axis
		 if((bbox.max1.x-bbox.min1.x)>=(bbox.max1.y-bbox.min1.y) && (bbox.max1.x-bbox.min1.x)>=(bbox.max1.z-bbox.min1.z))
		 {
			 splittingValue = (bbox.max1.x-bbox.min1.x)/2;
			 splittingAxis=0;
		 }
		 //y is the longest axis
		 else if((bbox.max1.y-bbox.min1.y)>=(bbox.max1.x-bbox.min1.x) && (bbox.max1.y-bbox.min1.y)>=(bbox.max1.z-bbox.min1.z))
		 {
			 splittingValue = (bbox.max1.y-bbox.min1.y)/2;
			 splittingAxis=1;
		 }

		 //z is the longest axis
		 else
		 {
			 splittingValue = (bbox.max1.z-bbox.min1.z)/2;
			 splittingAxis=2;
		 }
		
		  //sort objects (left or right) depending on their position relative to the splitting axis	
		 for (int i=0;i<listOfObjects.size();i++)
		 {
			 switch(splittingAxis)
			 {
			 case 0:
				 if ((*listOfObjects[i]).getCenter().x < splittingValue)
					 {
						leftObjects.push_back(listOfObjects[i]);
					 }
				 else
					{
					    rightObjects.push_back(listOfObjects[i]);
					}
			 break;
			 case 1:
				 if ((*listOfObjects[i]).getCenter().y < splittingValue)
					 {
						leftObjects.push_back(listOfObjects[i]);
					 }
				 else
					{
					    rightObjects.push_back(listOfObjects[i]);
					}
			 break;
			 case 2:
				 if ((*listOfObjects[i]).getCenter().z < splittingValue)
					 {
						leftObjects.push_back(listOfObjects[i]);
					 }
				 else
					{
					    rightObjects.push_back(listOfObjects[i]);
					}
			 break;
			 }
			 
		 }
		
		 BuildBVH(node->leftChild, leftObjects);
		 BuildBVH(node->rightChild, rightObjects);
	}

	 Point BVH::getCenter() const
	 {
		 return Point();
	 }
}