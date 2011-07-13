#include "HoughTransform.h"
#include <cmath>

using namespace std;

Comrade::IrisXT::HoughTransformObject::HoughTransformObject()
{}

Comrade::IrisXT::HoughTransformObject::~HoughTransformObject()
{}

int** Comrade::IrisXT::StraightLineDetector::return_array()
{
	return param_array;
}

void Comrade::IrisXT::StraightLineDetector::allocate(int r,int c)
{
    cout<<"StraightLineDetector object created...\n";

    rows=r;
    cols=c;

    param_array=new int*[rows];

    for (int i=0; i<=r-1; i++)
    {
        param_array[i]=new int[cols];
    }
    
    for (int i=0; i<=rows-1; i++)
    {
	    for (int j=0; j<=cols-1; j++)
	    {
		    param_array[i][j]=0;
	    }
    }
}

void Comrade::IrisXT::StraightLineDetector::deallocate()
{
    for (int i=0; i<=rows-1; i++)
    {
        delete[] param_array[i];
    }

    delete[] param_array;
}

Comrade::IrisXT::StraightLineDetector::StraightLineDetector(int perp_levels,int theta_levels)
{
    allocate(perp_levels,theta_levels);
}

void Comrade::IrisXT::StraightLineDetector::set_param(int perp_levels,int theta_levels)
{
    deallocate();
    allocate(perp_levels,theta_levels);
}

void Comrade::IrisXT::StraightLineDetector::transform(Buffer<RGB>* ip)
{
    deallocate();
    int l=ip->maxx;
    int b=ip->maxy;
    
    int h=abs(l)+abs(b);
    allocate(h,180);
	cout<<"Doing Hough Transform now...\n";
	
    for (int y=0; y<=ip->maxy-1; y++)
    {
	    for (int x=0; x<=ip->maxx-1; x++)
	    {
			RGB color=ip->at(x,y);
			
			if (color.red==255 && color.green==255 && color.blue==255)
		    {
			    for (int i=0; i<=179; i++)
				{	    
					double ang=deg_to_rad(i);
					double perp=x*cos(ang)+y*sin(ang);
				
					if (perp>=0 && perp<=h-1)
					{
						param_array[static_cast<int>(perp)][i]++;
					}
				}
			}
		}
	}
}

Comrade::IrisXT::StraightLineDetector::~StraightLineDetector()
{
    deallocate();
}


