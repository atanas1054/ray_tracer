#include <rt/groups/bvh.h>
#include <iostream>
#include <algorithm>
#include <map>
#include <iostream>

#define AXIS_X 0
#define AXIS_Y 1
#define AXIS_Z 2


namespace rt {

	void BVH::add(Primitive* p)
	{
		primitives.push_back(p);
		
	}

	void BVH::setMaterial(Material* m)
	{
		for(int i = 0;i < primitives.size(); i++)
		{
			(*primitives[i]).setMaterial(m);
		}
	}

	void BVH::setCoordMapper(CoordMapper* cm)
	{
		for(int i = 0;i < primitives.size(); i++)
		{
			(*primitives[i]).setCoordMapper(cm);
		}
	}

	Intersection BVH::intersect(const Ray& ray, float previousBestDistance) const
	{
		return IntersectNode(*root, ray, previousBestDistance);
	}

	Intersection BVH::IntersectNode(const Node& node, const Ray& ray, float bestDist) const
	{
		std::pair<float, float> boxIntersect = node.bbox.intersect(ray);
		if(boxIntersect.first < boxIntersect.second+epsilon && boxIntersect.first < bestDist)
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
						if(!nodeInt || itr.distance < nodeInt.distance+epsilon)
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

		return root->bbox;
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
		 return root->bbox.min+(root->bbox.max-root->bbox.min)/2;
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
		 
		 //int splittingAxis;
		 //x is the longest axis
		 //if((bbox.max.x-bbox.min.x)>=(bbox.max.y-bbox.min.y) && (bbox.max.x-bbox.min.x)>=(bbox.max.z-bbox.min.z))
		 //{
			// splittingAxis=AXIS_X;
		 //}
		 ////y is the longest axis
		 //else if((bbox.max.y-bbox.min.y)>=(bbox.max.x-bbox.min.x) && (bbox.max.y-bbox.min.y)>=(bbox.max.z-bbox.min.z))
		 //{
			// splittingAxis=AXIS_Y;
		 //}		 

		 ////z is the longest axis
		 //else
		 //{
			// splittingAxis=AXIS_Z;
		 //}

		  std::pair <float,float> splitAndCostX = findSAHSplitValue(listOfObjects, bbox,AXIS_X, 0, 1);
		  std::pair <float,float> splitAndCostY = findSAHSplitValue(listOfObjects, bbox,AXIS_Y, 0, 1);
		  std::pair <float,float> splitAndCostZ = findSAHSplitValue(listOfObjects, bbox,AXIS_Z, 0, 1);

		  
		 int splittingAxis;
		 float splittingValue;
		 if (splitAndCostX.second<=splitAndCostY.second && splitAndCostX.second<=splitAndCostZ.second)
		 {
			 splittingAxis = AXIS_X;
			 splittingValue = splitAndCostX.first;
		 }
		 else if(splitAndCostY.second<=splitAndCostX.second && splitAndCostY.second<=splitAndCostZ.second)
		 {
			 splittingAxis = AXIS_Y;
			 splittingValue = splitAndCostY.first;
		 }
		 else{
			 splittingAxis = AXIS_Z;
			 splittingValue = splitAndCostZ.first;
		 }

		 //sort objects (left or right) depending on their position relative to the splitting axis	
		 SplitObjByAxisValue(listOfObjects, splittingAxis, splittingValue, leftObjects, rightObjects);
		 
		 //in case splitting in the middle axis doesn't work
		 if(leftObjects.size() == 0 || rightObjects.size() == 0)
		 {
			 SplitObjByAxisSorting(listOfObjects, splittingAxis, leftObjects, rightObjects);
		 }
		 
		// std::cout << leftObjects.size() << " " << rightObjects.size() << "\n";

		 BuildBVHwithSAH(node->leftChild, leftObjects);
		 BuildBVHwithSAH(node->rightChild, rightObjects);
	}

	std::pair <float,float> BVH::findSAHSplitValue(std::vector<Primitive*> &listOfObjects, BBox &bbox, int axis, float rangeMin , float rangeMax)
	{
		int n = 2;
		int minIndex = -1;
		float minSplit = 0;
		float minCost = FLT_MAX;
		float* cost = new float[n];
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
			cost[i] = calcCost(listOfObjects,bbox,splitVal,axis);
			if(minCost > cost[i] ){
				minIndex = i;
				minCost = cost[i];
				minSplit = splitVal;
			}
		}
		return std::make_pair(minSplit,minCost);
	}

	float BVH::calcCost(std::vector<Primitive*> &listOfObjects, BBox &bbox,float splitValue,int axis)
	{
		//cost = areaOfbbox(LEFT)/bboxArea*countOfprimitives(LEFT) + areaOfbbox(RIGHT)/bboxArea*countOfprimitives(RIGHT)
		float cost;
		float bboxArea;
		float areaLeft=0,areaRight=0,countLeft=0,countRight=0;
		BBox right,left;
		bboxArea = calcBBoxArea(bbox);

		switch(axis)
			{
				case AXIS_X:
					left = BBox::empty();
					/*left.max.x = splitValue;
					areaLeft =  calcBBoxArea(left)-(left.max.y-left.min.y)*(left.max.z-left.min.z);
*/
					right = BBox::empty();
					/*right.min.x = splitValue;
					areaRight = calcBBoxArea(right)-(right.max.y-right.min.y)*(right.max.z-right.min.z);
*/
					for(int i=0;i<listOfObjects.size();i++)
					{
						if((*listOfObjects[i]).getCenter().x < splitValue)
						{
							countLeft++;
							left.extend((*listOfObjects[i]).getBounds());
						}
						else
						{
							countRight++;
							right.extend((*listOfObjects[i]).getBounds());
						}
					}
					areaLeft = calcBBoxArea(left);
					areaRight = calcBBoxArea(right);
					cost = (areaLeft/bboxArea)*countLeft +  (areaRight/bboxArea)*countRight;
					
					break;
				case AXIS_Y:
					
					left = BBox::empty();
					/*left.max.y = splitValue;
					areaLeft =  calcBBoxArea(left)-(left.max.x-left.min.x)*(left.max.z-left.min.z);
*/
					right = BBox::empty();
					/*right.min.y = splitValue;
					areaRight = calcBBoxArea(right)-(right.max.x-right.min.x)*(right.max.z-right.min.z);
*/
					for(int i=0;i<listOfObjects.size();i++)
					{
						if((*listOfObjects[i]).getCenter().y < splitValue)
						{
							countLeft++;
							left.extend((*listOfObjects[i]).getBounds());
						}
						else
						{
							countRight++;
							right.extend((*listOfObjects[i]).getBounds());
						}
					}
					areaLeft = calcBBoxArea(left);
					areaRight = calcBBoxArea(right);
					cost = (areaLeft/bboxArea)*countLeft +  (areaRight/bboxArea)*countRight;
					break;
				default:
					left = BBox::empty();
					/*left.max.z = splitValue;
					areaLeft =  calcBBoxArea(left)-(left.max.x-left.min.x)*(left.max.y-left.min.y);
*/
					right = BBox::empty();
					/*right.min.z = splitValue;
					areaRight = calcBBoxArea(right)-(right.max.x-right.min.x)*(right.max.y-right.min.y);
*/					
					for(int i=0;i<listOfObjects.size();i++)
					{
						if((*listOfObjects[i]).getCenter().z < splitValue)
						{
							left.extend((*listOfObjects[i]).getBounds());
							countLeft++;
						}
						else
						{
							right.extend((*listOfObjects[i]).getBounds());
							countRight++;
						}
					}
					areaLeft = calcBBoxArea(left);
					areaRight = calcBBoxArea(right);
					cost = (areaLeft/bboxArea)*countLeft +  (areaRight/bboxArea)*countRight;
					break;
			}
		
		/*std::cout<<countLeft<<" "<<countRight<<" cost= "<<cost;
		std::cout<<std::endl;*/
		
		return cost;
	}

	float BVH::calcBBoxArea(BBox &bbox)
	{
		float bbox_x,bbox_y,bbox_z,bboxArea;
		bbox_x = (bbox.max.x - bbox.min.x);
		bbox_y = (bbox.max.y - bbox.min.y);
		bbox_z = (bbox.max.z - bbox.min.z);
		bboxArea = 2* ( bbox_x*bbox_y +  bbox_x*bbox_z + bbox_y*bbox_z);

		return bboxArea;
	}

}

