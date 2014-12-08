#include <core/matrix.h>
#include <core/vector.h>
#include <core/point.h>

namespace rt {

	Matrix Matrix::invert() const {
    Matrix result;
    const Matrix& m = *this;

    //Taken and modified from http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
    result[0][0] = m[1][1] * m[2][2] * m[3][3] - m[1][1] * m[2][3] * m[3][2] - m[2][1] * m[1][2] * m[3][3] + m[2][1] * m[1][3] * m[3][2] + m[3][1] * m[1][2] * m[2][3] - m[3][1] * m[1][3] * m[2][2];
    result[1][0] = -m[1][0] * m[2][2] * m[3][3] + m[1][0] * m[2][3] * m[3][2] + m[2][0] * m[1][2] * m[3][3] - m[2][0] * m[1][3] * m[3][2] - m[3][0] * m[1][2] * m[2][3] + m[3][0] * m[1][3] * m[2][2];
    result[2][0] = m[1][0] * m[2][1] * m[3][3] - m[1][0] * m[2][3] * m[3][1] - m[2][0] * m[1][1] * m[3][3] + m[2][0] * m[1][3] * m[3][1] + m[3][0] * m[1][1] * m[2][3] - m[3][0] * m[1][3] * m[2][1];
    result[3][0] = -m[1][0] * m[2][1] * m[3][2] + m[1][0] * m[2][2] * m[3][1] + m[2][0] * m[1][1] * m[3][2] - m[2][0] * m[1][2] * m[3][1] - m[3][0] * m[1][1] * m[2][2] + m[3][0] * m[1][2] * m[2][1];

    float det = m[0][0] * result[0][0] + m[0][1] * result[1][0] + m[0][2] * result[2][0] + m[0][3] * result[3][0];
    if (det == 0)
        return Matrix::zero();

    result[0][1] = -m[0][1] * m[2][2] * m[3][3] + m[0][1] * m[2][3] * m[3][2] + m[2][1] * m[0][2] * m[3][3] - m[2][1] * m[0][3] * m[3][2] - m[3][1] * m[0][2] * m[2][3] + m[3][1] * m[0][3] * m[2][2];
    result[1][1] = m[0][0] * m[2][2] * m[3][3] - m[0][0] * m[2][3] * m[3][2] - m[2][0] * m[0][2] * m[3][3] + m[2][0] * m[0][3] * m[3][2] + m[3][0] * m[0][2] * m[2][3] - m[3][0] * m[0][3] * m[2][2];
    result[2][1] = -m[0][0] * m[2][1] * m[3][3] + m[0][0] * m[2][3] * m[3][1] + m[2][0] * m[0][1] * m[3][3] - m[2][0] * m[0][3] * m[3][1] - m[3][0] * m[0][1] * m[2][3] + m[3][0] * m[0][3] * m[2][1];
    result[3][1] = m[0][0] * m[2][1] * m[3][2] - m[0][0] * m[2][2] * m[3][1] - m[2][0] * m[0][1] * m[3][2] + m[2][0] * m[0][2] * m[3][1] + m[3][0] * m[0][1] * m[2][2] - m[3][0] * m[0][2] * m[2][1];
    result[0][2] = m[0][1] * m[1][2] * m[3][3] - m[0][1] * m[1][3] * m[3][2] - m[1][1] * m[0][2] * m[3][3] + m[1][1] * m[0][3] * m[3][2] + m[3][1] * m[0][2] * m[1][3] - m[3][1] * m[0][3] * m[1][2];
    result[1][2] = -m[0][0] * m[1][2] * m[3][3] + m[0][0] * m[1][3] * m[3][2] + m[1][0] * m[0][2] * m[3][3] - m[1][0] * m[0][3] * m[3][2] - m[3][0] * m[0][2] * m[1][3] + m[3][0] * m[0][3] * m[1][2];
    result[2][2] = m[0][0] * m[1][1] * m[3][3] - m[0][0] * m[1][3] * m[3][1] - m[1][0] * m[0][1] * m[3][3] + m[1][0] * m[0][3] * m[3][1] + m[3][0] * m[0][1] * m[1][3] - m[3][0] * m[0][3] * m[1][1];
    result[3][2] = -m[0][0] * m[1][1] * m[3][2] + m[0][0] * m[1][2] * m[3][1] + m[1][0] * m[0][1] * m[3][2] - m[1][0] * m[0][2] * m[3][1] - m[3][0] * m[0][1] * m[1][2] + m[3][0] * m[0][2] * m[1][1];
    result[0][3] = -m[0][1] * m[1][2] * m[2][3] + m[0][1] * m[1][3] * m[2][2] + m[1][1] * m[0][2] * m[2][3] - m[1][1] * m[0][3] * m[2][2] - m[2][1] * m[0][2] * m[1][3] + m[2][1] * m[0][3] * m[1][2];
    result[1][3] = m[0][0] * m[1][2] * m[2][3] - m[0][0] * m[1][3] * m[2][2] - m[1][0] * m[0][2] * m[2][3] + m[1][0] * m[0][3] * m[2][2] + m[2][0] * m[0][2] * m[1][3] - m[2][0] * m[0][3] * m[1][2];
    result[2][3] = -m[0][0] * m[1][1] * m[2][3] + m[0][0] * m[1][3] * m[2][1] + m[1][0] * m[0][1] * m[2][3] - m[1][0] * m[0][3] * m[2][1] - m[2][0] * m[0][1] * m[1][3] + m[2][0] * m[0][3] * m[1][1];
    result[3][3] = m[0][0] * m[1][1] * m[2][2] - m[0][0] * m[1][2] * m[2][1] - m[1][0] * m[0][1] * m[2][2] + m[1][0] * m[0][2] * m[2][1] + m[2][0] * m[0][1] * m[1][2] - m[2][0] * m[0][2] * m[1][1];

    result = result*(1.0f/det);
    return result;
}
	Matrix::Matrix(const Float4& r1, const Float4& r2, const Float4& r3, const Float4& r4)
	{
		Matrix m = *this;
		
		m[0][0] = r1[0];
		m[0][1] = r1[1];
		m[0][2] = r1[2];
		m[0][3] = r1[3];

		m[1][0] = r2[0];
		m[1][1] = r2[1];
		m[1][2] = r2[2];
		m[1][3] = r2[3];

		m[2][0] = r3[0];
		m[2][1] = r3[1];
		m[2][2] = r3[2];
		m[2][3] = r3[3];

		m[3][0] = r4[0];
		m[3][1] = r4[1];
		m[3][2] = r4[2];
		m[3][3] = r4[3];
	}

	Matrix Matrix::zero()
	{
		Matrix m;

		for (int i=0;i<4;i++)
			for (int j=0;j<4;j++)
			{
				m[i][j] = 0;
			}

		return m;
	}

	Matrix Matrix::identity()
	{
		Matrix m;

		for (int i=0;i<4;i++)
			for (int j=0;j<4;j++)
			{
				if (i==j)
					m[i][j] = 1;
				else
				m[i][j] = 0;
			}

		return m;
	}

	 Float4& Matrix::operator[](int idx)
	 {
		 Matrix m = *this;
		 Float4 f;
		 f.x = m[idx][0];
		 f.y = m[idx][1];
		 f.z = m[idx][2];
		 f.w = m[idx][3];

		 return f;
	 }

	  Float4 Matrix::operator[](int idx) const
	 {
		 Matrix m = *this;
		 Float4 f;
		 f.x = m[idx][0];
		 f.y = m[idx][1];
		 f.z = m[idx][2];
		 f.w = m[idx][3];

		 return f;
	 }

	   Float4 Matrix::operator*(const Float4& b) const
	   {
		   const Matrix& m = *this;

		   Float4 result;

		   result.x = dot(m[0],b);
		   result.y = dot(m[1],b);
		   result.z = dot(m[2],b);
		   result.w = dot(m[3],b);

		   return result;
	   }

	   Vector Matrix::operator*(const Vector& b) const
	   {
		   const Matrix& m = *this;
		   Float4 result = m*Float4(b.x,b.y,b.z,0);
		   return Vector(result.x,result.y,result.z);
	   }

	   Point Matrix::operator*(const Point& b) const
	   {
		   const Matrix& m = *this;
		   Float4 result = m*Float4(b.x,b.y,b.z,1);
		   return Point(result.x,result.y,result.z);
	   }
}

