#include <rt/groups/bvh.h>

namespace rt {

	void BVH::add(Primitive* p)
	{
		primitives.push_back(p);
	}

	void BVH::rebuildIndex()
	{
		BuildBVH(root,primitives);
	}

	void BVH::BuildBVH(Node* node, std::vector<Primitive*> listOfObjects)
	{
		BBox bbox;
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
		 

		 //calculate splitting plane (along the longest axis)

		 for (int i=0;i<listOfObjects.size();i++)
		 {
			 /*if ((*listOfObjects[i]).getCenter() < splitting plane)
			 {
				 leftObjects.push_back(listOfObjects[i]);
			 }
			 else
			 {
				 rightObjects.push_back(listOfObjects[i]);
			 }*/
		 }
		
		 BuildBVH(node->leftChild, leftObjects);
		 BuildBVH(node->rightChild, rightObjects);
	}
}