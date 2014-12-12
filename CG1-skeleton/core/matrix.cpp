#include <core/matrix.h>
#include <core/vector.h>
#include <core/point.h>
#include <core/float4.h>

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
		row0 = r1;
		row1= r2;
		row2= r3;
		row3 = r4;
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
		 if (idx==0)
			 return row0;
		 if (idx==1)
			 return row1;
		 if (idx==2)
			 return row2;
		 if (idx==3)
			 return row3;
		 if (idx>3)
			 return Float4::rep(0);

	 }

	  Float4 Matrix::operator[](int idx) const
	 {
		if (idx==0)
			 return row0;
		 if (idx==1)
			 return row1;
		 if (idx==2)
			 return row2;
		 if (idx==3)
			 return row3;
		 if (idx>3)
			 return Float4::rep(0);
	 }
		
	  Matrix Matrix::operator+(const Matrix& b) const
	  {
		  const Matrix& m = *this;
		  Matrix result;
		  for(int i=0;i<4;i++)
			  for(int j=0;j<4;j++)
			  {
				  result[i][j] = m[i][j] + b[i][j];
			  }
		  return result;
	  }

	  Matrix Matrix::operator-(const Matrix& b) const
	  {
		  const Matrix& m = *this;
		  Matrix result;
		  for(int i=0;i<4;i++)
			  for(int j=0;j<4;j++)
			  {
				  result[i][j] = m[i][j] - b[i][j];
			  }
		  return result;
	  }

	  Matrix Matrix::transpose() const
	  {
		const Matrix& m = *this;
		Matrix temp;

		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
			{
				temp[i][j] = m[j][i];
			}
		return temp;
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

	    bool Matrix::operator==(const Matrix& b) const
		{
			const Matrix& m = *this;

			for(int i=0;i<4;i++)
				for(int j=0;j<4;j++)
				{
					if (m[i][j]!=b[i][j])
						return false;
				}
			return true;
		}

		bool Matrix::operator!=(const Matrix& b) const
		{
			const Matrix& m = *this;

			for(int i=0;i<4;i++)
				for(int j=0;j<4;j++)
				{
					if (m[i][j]!=b[i][j])
						return true;
				}
			return false;
		}

		float Matrix::det() const
		{
		Matrix result;
		const Matrix& m = *this;

		result[0][0] = m[1][1] * m[2][2] * m[3][3] - m[1][1] * m[2][3] * m[3][2] - m[2][1] * m[1][2] * m[3][3] + m[2][1] * m[1][3] * m[3][2] + m[3][1] * m[1][2] * m[2][3] - m[3][1] * m[1][3] * m[2][2];
		result[1][0] = -m[1][0] * m[2][2] * m[3][3] + m[1][0] * m[2][3] * m[3][2] + m[2][0] * m[1][2] * m[3][3] - m[2][0] * m[1][3] * m[3][2] - m[3][0] * m[1][2] * m[2][3] + m[3][0] * m[1][3] * m[2][2];
		result[2][0] = m[1][0] * m[2][1] * m[3][3] - m[1][0] * m[2][3] * m[3][1] - m[2][0] * m[1][1] * m[3][3] + m[2][0] * m[1][3] * m[3][1] + m[3][0] * m[1][1] * m[2][3] - m[3][0] * m[1][3] * m[2][1];
		result[3][0] = -m[1][0] * m[2][1] * m[3][2] + m[1][0] * m[2][2] * m[3][1] + m[2][0] * m[1][1] * m[3][2] - m[2][0] * m[1][2] * m[3][1] - m[3][0] * m[1][1] * m[2][2] + m[3][0] * m[1][2] * m[2][1];

		float det = m[0][0] * result[0][0] + m[0][1] * result[1][0] + m[0][2] * result[2][0] + m[0][3] * result[3][0];
		return det;
		}

		Matrix Matrix::system(const Vector& e1, const Vector& e2, const Vector& e3)
		{
			Matrix result;
			return result;
		}

		Matrix product(const Matrix& a, const Matrix& b)
		{
			Matrix result;

			for(int i = 0; i < 4; i++){ 
				for(int j = 0; j < 4; j++){ 
					for(int x = 0; x < 4; x++) 
						result[i][j] += a[i][x] * b[x][j]; 
				} 
			} 

			return result;
		}

		Matrix operator*(const Matrix& a, float scalar)
		{
			Matrix result;
			for (int i=0;i<4;i++)
				for (int j=0;j<4;j++)
				{
					result[i][j] = a[i][j] * scalar;
				}
			return result;
		}

		Matrix operator*(float scalar, const Matrix& a)
			{
			Matrix result;
			for (int i=0;i<4;i++)
				for (int j=0;j<4;j++)
				{
					result[i][j] = a[i][j] * scalar;
				}
			return result;
		}
}

