#include <rt/groups/bvh.h>
#include <iostream>
#include <algorithm>
#include <map>

#define AXIS_X 0
#define AXIS_Y 1
#define AXIS_Z 2


namespace rt {

	void BVH::add(Primitive* p)
	{
		primitives.push_back(p);
	}

	Intersection BVH::intersect(const Ray& ray, float previousBestDistance) const
	{
		return IntersectNode(*root, ray, previousBestDistance);
	}

	Intersection BVH::IntersectNode(const Node& node, const Ray& ray, float bestDist) const
	{
		std::pair<float, float> boxIntersect = node.bbox.intersect(ray);
		if(boxIntersect.first < boxIntersect.second && boxIntersect.first < bestDist && boxIntersect.first > 0)
		{
			Intersection nodeInt = Intersection::failure();
			if(node.objectList.empty())
			{
				//AABox aabox = AABox((*node.rightChild).bbox.min, (*node.rightChild).bbox.max, nullptr, nullptr);
				//return aabox.intersect(ray, bestDist);
				Intersection leftInt = IntersectNode(*node.leftChild, ray, bestDist);
				Intersection rightInt = IntersectNode(*node.rightChild, ray, bestDist);
				if(leftInt && rightInt)
				{
					nodeInt = leftInt.distance < rightInt.distance ? leftInt : rightInt;
				}else if(leftInt){
					nodeInt = leftInt;
				}else if(rightInt){
					nodeInt = rightInt;
				}
				if(nodeInt.distance < bestDist)
					return nodeInt;
			}else{
				Intersection itr;
				for(int i = 0; i < node.objectList.size();i++)
				{
					itr = (*node.objectList[i]).intersect(ray, bestDist);
					if(itr && itr.distance < bestDist)
					{
						if(!nodeInt || itr.distance < nodeInt.distance)
						nodeInt = itr;
					}
				}
				return nodeInt;
			}
		}
		return Intersection::failure();
	}

	BBox BVH::getBounds() const
	{

		return BBox::empty();
	}

	void BVH::rebuildIndex()
	{
		BuildBVH(root,primitives);
	}

	void BVH::BuildBVH(Node* &node, std::vector<Primitive*> listOfObjects)
	{
		node = new Node;
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
		 if((bbox.max.x-bbox.min.x)>=(bbox.max.y-bbox.min.y) && (bbox.max.x-bbox.min.x)>=(bbox.max.z-bbox.min.z))
		 {
			 splittingValue = (bbox.max.x+bbox.min.x)/2;
			 splittingAxis=AXIS_X;
		 }
		 //y is the longest axis
		 else if((bbox.max.y-bbox.min.y)>=(bbox.max.x-bbox.min.x) && (bbox.max.y-bbox.min.y)>=(bbox.max.z-bbox.min.z))
		 {
			 splittingValue = (bbox.max.y+bbox.min.y)/2;
			 splittingAxis=AXIS_Y;
		 }

		 //z is the longest axis
		 else
		 {
			 splittingValue = (bbox.max.z+bbox.min.z)/2;
			 splittingAxis=AXIS_Z;
		 }
		
		 //sort objects (left or right) depending on their position relative to the splitting axis	
		 SplitObjByAxisValue(listOfObjects, splittingAxis, splittingValue, leftObjects, rightObjects);
		 
		 //in case splitting in the middle axis doesn't work
		 if(leftObjects.size() == 0 || rightObjects.size() == 0)
		 {
			 SplitObjByAxisSorting(listOfObjects, splittingAxis, leftObjects, rightObjects);
		 }
		 
		 //std::cout << leftObjects.size() << " " << rightObjects.size() << "\n";

		 BuildBVH(node->leftChild, leftObjects);
		 BuildBVH(node->rightChild, rightObjects);
	}

	void BVH::SplitObjByAxisSorting(std::vector<Primitive*>& listObj, int axisCode, std::vector<Primitive*> &leftObj, std::vector<Primitive*> &rightObj)
	{
		leftObj.clear();
		rightObj.clear();

		switch(axisCode)
		{
			case AXIS_X:
				std::sort (listObj.begin(), listObj.end(), [](Primitive* a, Primitive* b) { return (*a).getCenter().x < (*b).getCenter().x; });
				break;
			case AXIS_Y:
				std::sort (listObj.begin(), listObj.end(), [](Primitive* a, Primitive* b) { return (*a).getCenter().x < (*b).getCenter().x; });
				break;
			default:
				std::sort (listObj.begin(), listObj.end(), [](Primitive* a, Primitive* b) { return (*a).getCenter().x < (*b).getCenter().x; });
				break;
		}

		for (int i = 0 ; i < listObj.size();i++)
		{
			if(i < listObj.size() / 2){
				leftObj.push_back(listObj[i]);
			} else {
				rightObj.push_back(listObj[i]);
			}
		}
	}

	void BVH::SplitObjByAxisValue(std::vector<Primitive*> &listObj, int axisCode, float splitVal, std::vector<Primitive*> &leftObj, std::vector<Primitive*> &rightObj)
	{
		leftObj.clear();
		rightObj.clear();
		for (int i=0;i<listObj.size();i++)
		 {
			 switch(axisCode)
			 {
			 case 0:
				 if ((*listObj[i]).getCenter().x < splitVal)
					 {
						leftObj.push_back(listObj[i]);
					 }
				 else
					{
					    rightObj.push_back(listObj[i]);
					}
			 break;
			 case 1:
				 if ((*listObj[i]).getCenter().y < splitVal)
					 {
						leftObj.push_back(listObj[i]);
					 }
				 else
					{
					    rightObj.push_back(listObj[i]);
					}
			 break;
			 case 2:
				 if ((*listObj[i]).getCenter().z < splitVal)
					 {
						leftObj.push_back(listObj[i]);
					 }
				 else
					{
					    rightObj.push_back(listObj[i]);
					}
			 break;
			 }
			 
		 }
	}


	 Point BVH::getCenter() const
	 {
		 return Point();
	 }

	 void BVH::BuildBVH2(Node* &node, std::vector<Primitive*> listOfObjects)
	{
		node = new Node;
		BBox bbox = BBox::empty();

		 std::vector<Primitive*> leftObjects;
		 std::vector<Primitive*> rightObjects;
		 std::multimap<float,Primitive*> orderedObjects;
		
		for(int i = 0;i < listOfObjects.size(); i++)
		{
			bbox.extend((*listOfObjects[i]).getBounds());
		}

		node->bbox = bbox;

		if(listOfObjects.size()<=3)
		{
			node->objectList = listOfObjects;
			return;
		}

		
		 float splittingValue;
		 int splittingAxis;
		 //x is the longest axis
		 if((bbox.max.x-bbox.min.x)>=(bbox.max.y-bbox.min.y) && (bbox.max.x-bbox.min.x)>=(bbox.max.z-bbox.min.z))
		 {
			 //splittingValue = bbox.min.x+(bbox.max.x-bbox.min.x)/2;
			 splittingAxis=0;
		 }
		 //y is the longest axis
		 else if((bbox.max.y-bbox.min.y)>=(bbox.max.x-bbox.min.x) && (bbox.max.y-bbox.min.y)>=(bbox.max.z-bbox.min.z))
		 {
			 //splittingValue = bbox.min.y+(bbox.max.y-bbox.min.y)/2;
			 splittingAxis=1;
		 }

		 //z is the longest axis
		 else
		 {
			 //splittingValue = bbox.min.z+(bbox.max.z-bbox.min.z)/2;
			 splittingAxis=2;
		 }
		 
		 
		  //sort objects (left or right) depending on their position relative to the splitting axis	
		 for (int i=0;i<listOfObjects.size();i++)
		 {
			 
			 switch(splittingAxis)
			 {
			 case 0:
				
						//tempObjects.push_back((*listOfObjects[i]).getCenter().x);
						orderedObjects.insert ( std::pair<float,Primitive*>((*listOfObjects[i]).getCenter().x,(listOfObjects[i])));
						
				
			 break;
			 case 1:
				 		//tempObjects.push_back((*listOfObjects[i]).getCenter().y );
						orderedObjects.insert ( std::pair<float,Primitive*>((*listOfObjects[i]).getCenter().y,(listOfObjects[i])));
						
			 break;
			 case 2:
						//tempObjects.push_back((*listOfObjects[i]).getCenter().z);
						orderedObjects.insert ( std::pair<float,Primitive*>((*listOfObjects[i]).getCenter().z,(listOfObjects[i])));
						
			 break;
			 }
			
		 }
			//sort tempObjects;
			//take the median
		std::vector<float> splittingValues;
	
		for(std::multimap<float, Primitive*>::const_iterator it = orderedObjects.begin(); it != orderedObjects.end(); it++)
			{
				splittingValues.push_back(it->first);
			}

		float median;
		if ((splittingValues.size() % 2) == 0) 
        median = (splittingValues[splittingValues.size()/2] + splittingValues[(splittingValues.size()/2) - 1])/2.0;	 
		else 
        median = splittingValues[splittingValues.size()/2]; 

		for(std::multimap<float, Primitive*>::const_iterator it = orderedObjects.begin(); it != orderedObjects.end(); it++)
			{
				if(it->first<median)
					leftObjects.push_back(it->second);
				else
					rightObjects.push_back(it->second);
			}


		/* std::cout<<leftObjects.size()<<" "<<rightObjects.size();
		 std::cout<<std::endl;*/
		 BuildBVH2(node->leftChild, leftObjects);
		 BuildBVH2(node->rightChild, rightObjects);
	}


	void BVH::BuildBVHwithSAH(Node* &node, std::vector<Primitive*> listOfObjects)
	{
		node = new Node;
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
		 
		 int splittingAxis;
		 //x is the longest axis
		 if((bbox.max.x-bbox.min.x)>=(bbox.max.y-bbox.min.y) && (bbox.max.x-bbox.min.x)>=(bbox.max.z-bbox.min.z))
		 {
			 splittingAxis=AXIS_X;
		 }
		 //y is the longest axis
		 else if((bbox.max.y-bbox.min.y)>=(bbox.max.x-bbox.min.x) && (bbox.max.y-bbox.min.y)>=(bbox.max.z-bbox.min.z))
		 {
			 splittingAxis=AXIS_Y;
		 }

		 float splittingValue = findSAHSplitValue(listOfObjects, splittingAxis, 0, 1);
		 

		 //z is the longest axis
		 else
		 {
			 splittingAxis=AXIS_Z;
		 }


		
		 //sort objects (left or right) depending on their position relative to the splitting axis	
		 SplitObjByAxisValue(listOfObjects, splittingAxis, splittingValue, leftObjects, rightObjects);
		 
		 //in case splitting in the middle axis doesn't work
		 if(leftObjects.size() == 0 || rightObjects.size() == 0)
		 {
			 SplitObjByAxisSorting(listOfObjects, splittingAxis, leftObjects, rightObjects);
		 }
		 
		 //std::cout << leftObjects.size() << " " << rightObjects.size() << "\n";

		 BuildBVH(node->leftChild, leftObjects);
		 BuildBVH(node->rightChild, rightObjects);
	}

	float BVH::findSAHSplitValue(std::vector<Primitive*> &listOfObjects, BBox &bbox, int axis, float rangeMin , float rangeMax)
	{
		int n = 5;
		int minIndex = -1;
		float minSplit = 0;
		float minCost = FLT_MAX;
		int* cost = new int[n];
		float splitVal;
		for(int i = 0; i < n;i++)
		{
			splitVal = ((rangeMax - rangeMin) * i / n + rangeMin);
			switch(axis)
			{
				case AXIS_X:
					splitVal = (bbox.max.x - bbox.min.x) * splitVal  + bbox.min.x;
					break;
				case AXIS_Y:
					splitVal = (bbox.max.y - bbox.min.y) * splitVal  + bbox.min.y;
					break;
				default:
					splitVal = (bbox.max.z - bbox.min.z) * splitVal  + bbox.min.z;
					break;
			}
			cost[i] = calcCost(listOfObjects, splitVal);
			if(minCost > cost[i] ){
				minIndex = i;
				minCost = cost[i];
				minSplit = splitVal;
			}
		}
		return splitVal;
	}



}