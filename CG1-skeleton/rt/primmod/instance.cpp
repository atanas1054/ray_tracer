#include <rt/primmod/instance.h>
#include <iostream>
#include <vector>

namespace rt{

	Instance::Instance(Primitive* content): content_(content)
	{
		transformation = Matrix::identity();
		invTransformation = Matrix::identity();
	}
	
	Primitive* Instance::content()
	{
		return content_;
	}

	Point Instance::getCenter() const
	{
		
		BBox transformed_bbox = content_->getBounds();
		Point min_p = transformed_bbox.min;
		Point max_p = transformed_bbox.max;

		min_p = transformation*min_p;
		max_p = transformation*max_p;

		return Point(
			(min_p.x + max_p.x) / 2,
			(min_p.y + max_p.y) / 2,
			(min_p.z + max_p.z) / 2
		);
	}

    BBox  Instance::getBounds() const
	{
		Point* vec = new Point[8];
		BBox transformed_bbox = content_->getBounds();
		Point p1 = transformed_bbox.min;
		vec[0] = p1;
		vec[1]= (Point(transformed_bbox.max.x,p1.y,p1.z));
		vec[2]=(Point(p1.x,p1.y,transformed_bbox.max.z));
		vec[3]=(Point(p1.x,transformed_bbox.max.y,p1.z));
		vec[4]=(Point(transformed_bbox.max.x,transformed_bbox.max.y,p1.z));
		vec[5]=(Point(transformed_bbox.max.x,p1.y,transformed_bbox.max.z));
		vec[6]=(Point(p1.x,transformed_bbox.max.y,transformed_bbox.max.z));
		vec[7]=(Point(transformed_bbox.max.x,transformed_bbox.max.y,transformed_bbox.max.z));

		for(int i=0;i<8;i++)
		{
			vec[i] = transformation*vec[i];
		}

		Point min = vec[0];
		Point max = vec[0];
		for(int i=0;i<8;i++)
		{
			if(min.x > vec[i].x)
				min.x = vec[i].x;
			if(min.y > vec[i].y)
				min.y= vec[i].y;
			if(min.z > vec[i].z)
				min.z = vec[i].z;
			if(max.x < vec[i].x)
				max.x = vec[i].x;
			if(max.y < vec[i].y)
				max.y= vec[i].y;
			if(max.z < vec[i].z)
				max.z = vec[i].z;

		}

		return BBox(min,max);
	}

    Intersection  Instance::intersect(const Ray& ray, float previousBestDistance) const
	{
		//1.inverse transformation applied to the ray (point origin + direction)
		//2.check the archetype for intersection
		//3.transform the intersection point with the transformation matrix
		//4.transform the intersection normal with the transposed of the inverse transformation matrix

		float previousBestDistance_ = FLT_MAX;
		Ray inverse_ray(invTransformation * ray.o, (invTransformation * ray.d).normalize());
		
		if(previousBestDistance < FLT_MAX){
			Point p = ray.getPoint(previousBestDistance);
			p = invTransformation * p;
			previousBestDistance_ = (p - inverse_ray.o).length();
		}

		Intersection intersect = content_->intersect(inverse_ray, previousBestDistance_);
		if(intersect)
		{
			Point hitPoint = transformation * intersect.hitPoint();
			Vector normal = (invTransformation.transpose() * intersect.normal()).normalize();
			Point local = hitPoint - (getCenter() - Point::rep(0)) ;
			//
			float distance = (hitPoint - ray.o).length();
			return Intersection(distance, ray, intersect.solid, normal, local);
		}
		return Intersection::failure();
	}

    void  Instance::setMaterial(Material* m)
	{
		content_->setMaterial(m);
	}
	
    void  Instance::setCoordMapper(CoordMapper* cm)
	{
		content_->setCoordMapper(cm);
	}

	//reset transformation back to identity
	void Instance::reset()
	{
		transformation = transformation.identity();
		invTransformation = transformation;
	}

    void Instance::translate(const Vector& t)
	{
		Matrix translate  = Matrix::identity();
		translate[0][3] = t.x;
		translate[1][3] = t.y;
		translate[2][3] = t.z;

		transformation = product(translate, transformation);
		invTransformation = transformation.invert();
	}

    void Instance::rotate(const Vector& axis, float angle)
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
		invTransformation = transformation.invert();
	}

    void Instance::scale(float scale)
	{
		Matrix scale_matrix;
		scale_matrix = scale_matrix.identity();
		scale_matrix[0][0] = scale;
		scale_matrix[1][1] = scale;
		scale_matrix[2][2] = scale;

		transformation = product(scale_matrix, transformation);
		invTransformation = transformation.invert();
	}

    void Instance::scale(const Vector& scale)
	{
		Matrix scale_matrix;
		scale_matrix = scale_matrix.identity();
		scale_matrix[0][0] = scale.x;
		scale_matrix[1][1] = scale.y;
		scale_matrix[2][2] = scale.z;
		transformation = product(scale_matrix, transformation);
		invTransformation = transformation.invert();
	}

	void Instance::applyTransform(const Matrix& transformation_)
	{
		transformation = product(transformation,transformation_);
		invTransformation = transformation.invert();
	}

}