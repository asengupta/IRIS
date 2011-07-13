#include "Matrix4x4.h"

Comrade::Iris3D::Point Comrade::Iris3D::multiply(Comrade::Iris3D::Point coord, Comrade::Iris3D::Matrix4x4 transform)
{
	Comrade::Iris3D::Point answer;
  answer.input(0,0,0,0);

	for (int r=0; r<=MATRIX_Y-1;r++)
	{
		for (int c=0; c<=MATRIX_X-1; c++)
		{
			answer.array[0][r]+=coord.array[0][c]*transform.matrix[c][r];
		}
	}

	for (int x=0; x<=MATRIX_X-1; x++)
	{
		if (fabs(answer.array[0][x])<=6.2e-17)
			answer.array[0][x]=0.0;
	}

	return answer;
}

void Comrade::Iris3D::Point::input
(double a,double b,double c,double d)
{
    array[0][0]=a;
    array[0][1]=b;
    array[0][2]=c;
    array[0][3]=d;
}

void Comrade::Iris3D::Point::show()
{
    std::cout<<"("<<array[0][0]<<","<<array[0][1]<<","<<
    array[0][2]<<")";
    std::cout<<std::endl;
}

Comrade::Iris3D::Matrix4x4::Matrix4x4()
{
    init();
}


void Comrade::Iris3D::Matrix4x4::input(double arr[MATRIX_Y][MATRIX_X])
{
    for (int r=0; r<=MATRIX_Y-1; r++)
    {
        for (int c=0; c<=MATRIX_X-1; c++)
        {
            matrix[r][c]=arr[r][c];
        }
    }
}

void Comrade::Iris3D::Matrix4x4::show()
{
    for (int r=0; r<=MATRIX_Y-1; r++)
    {
        for (int c=0; c<=MATRIX_X-1; c++)
        {
            std::cout<<matrix[r][c]<<" ";
        }

        std::cout<<std::endl;
    }
}

void Comrade::Iris3D::Matrix4x4::init()
{
	for (int r=0; r<=MATRIX_Y-1; r++)
	{
		for (int c=0; c<=MATRIX_X-1; c++)
		{
			if (r==c)
            {
				matrix[r][c]=1;
            }

			else
            {
				matrix[r][c]=0;
            }
		}
	}
}

Comrade::Iris3D::Matrix4x4::~Matrix4x4()
{}


