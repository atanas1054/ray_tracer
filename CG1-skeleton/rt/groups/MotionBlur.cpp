#include <rt/groups/MotionBlur.h>
#include <rt/primmod/instance.h>
#include <core\random.h>
#include <core/interpolate.h>
#include <cmath>
namespace rt {

	BBox MotionBlur:: getBounds() const
	{
		BBox transformed_bbox = prim->getBounds();
		Point min_p = transformed_bbox.min;
		Point max_p = transformed_bbox.max;

		min_p = transformation*min_p;
		max_p = transformation*max_p;

		transformed_bbox.min = min_p;
		transformed_bbox.max = max_p;
		transformed_bbox.extend(prim->getBounds());
		return transformed_bbox;
	}
    Intersection MotionBlur::intersect(const Ray& ray, float previousBestDistance) const
	{
		Instance* normal = new Instance(prim);
		float rand = random();
		//rand = std::sqrt(rand);
		Matrix transformed_matrix = lerp(Matrix::identity(),transformation,rand);
		normal->applyTransform(transformed_matrix);

		return normal->intersect(ray,previousBestDistance);
	}
    void MotionBlur::rebuildIndex()
	{

	}
    void MotionBlur::add(Primitive* p)
	{
		prim = p;
	}
	Point MotionBlur::getCenter() const
	{
		return prim->getCenter();
	}
    void MotionBlur::setMaterial(Material* m)
	{
		prim->setMaterial(m);
	}
    void MotionBlur::setCoordMapper(CoordMapper* cm)
	{
		prim->setCoordMapper(cm);
	}
	void MotionBlur::translate(const Vector& t)
	{
		Matrix translate  = Matrix::identity();
		translate[0][3] = t.x;
		translate[1][3] = t.y;
		translate[2][3] = t.z;

		transformation = product(translate, transformation);
		
	 }

	void MotionBlur::rotate(const Vector& axis, float angle)
	{
		Vector axis_(axis.x,axis.y,axis.z);
		axis_ = axis_ / axis_.length();
		
		Matrix rotation_matrix = Matrix::identity();
		//taken from http://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_from_axis_and_angle
		rotation_matrix[0][0] = cos(angle) + axis_.x*axis_.x*(1-cos(angle));
		rotation_matrix[1][0] = axis_.y*axis_.x*(1-cos(angle)) + axis_.z*sin(angle);
		rotation_matrix[2][0] = axis_.z*axis_.x*(1-cos(angle)) - axis_.y*sin(angle);
		rotation_matrix[0][1] = axis_.x*axis_.y*(1-cos(angle)) - axis_.z*sin(angle);
		rotation_matrix[1][1] = cos(angle)+axis_.y*axis_.y*(1-cos(angle));
		rotation_matrix[2][1] = axis_.z*axis_.y*(1-cos(angle)) + axis_.x*sin(angle);
		rotation_matrix[0][2] = axis_.x*axis_.z*(1-cos(angle)) + axis_.y*sin(angle);
		rotation_matrix[1][2] = axis_.y*axis_.z*(1-cos(angle)) - axis_.x*sin(angle);
		rotation_matrix[2][2] = cos(angle) + axis_.z*axis_.z*(1-cos(angle));

		transformation = product(rotation_matrix, transformation);
		
	}

}