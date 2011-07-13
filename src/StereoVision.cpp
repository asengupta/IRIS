#include "StereoVision.h"

Comrade::Iris3D::DepthmapBuilder::DepthmapBuilder()
{
    std::cout<<"DepthmapBuilder object created...\n";
}

void Comrade::Iris3D::DepthmapBuilder::set_stepsize(int step)
{
	step_size=step;
}

void Comrade::Iris3D::DepthmapBuilder::build_depthmap
(Buffer<RGB>* left,Buffer<RGB>* right,Buffer<RGB>* dmap)
{
    int IMAGE_X=left->maxx;
    int IMAGE_Y=left->maxy;
    
    for (int y1=0; y1<=IMAGE_Y-1; y1+=step_size)
    {
        for (int x1=0; x1<=IMAGE_X-1; x1+=step_size)
        {
            cout<<"Doing ("<<x1<<","<<y1<<")\n";

            //int total=0;

            /*for (int i=y1; i<=y1+step_size; i++)
            {
                for (int j=x1; j<=x1+step_size; j++)
                {
                    if (op_buf.at(j,i).red==255 &&
                        op_buf.at(j,i).green==255 &&
                        op_buf.at(j,i).blue==255)
                    {
                        total++;
                    }
                }
            }

            double ratio=static_cast<double>(total)/(step_size*step_size);
            //cout<<total<<" "<<ratio<<endl;

            if (ratio<.1)
            {
                for (int i=y1; i<=y1+step_size; i++)
                {
                    for (int j=x1; j<=x1+step_size; j++)
                    {
                        dmap.at(j,i).red=255;
                        dmap.at(j,i).green==0;
                        dmap.at(j,i).blue=0;
                    }
                }

                continue;
            }*/

            std::vector<double> arr;
            //IMAGE_X-1-x1
            for (int i=0; i<=20; i++)
            {
                //cout<<"Now doing..."<<i<<endl;
                arr.push_back(correlate(left,right,x1,y1,x1+step_size,y1+step_size,x1+i,y1));
            }

            /*for (int i=0; i<=arr.size()-1; i++)
            {
                cout<<arr[i]<<" ";
            }*/

            double min=arr[0];
            int minpos=0;
            //double threshold=min-arr[0];

            for (unsigned int i=1; i<=arr.size()-1; i++)
            {
                if (arr[i]<min)
                {
                    min=arr[i];
                    minpos=i;
                }
            }

            cout<<"Minimum is at : "<<x1+minpos<<endl;
            unsigned char shade=static_cast<unsigned char>(511*(1-1./sqrt(minpos+1)));

            for (int i=y1; i<=y1+step_size; i++)
            {
                for (int j=x1; j<=x1+step_size; j++)
                {
                    dmap->at(j,i).red=
                    dmap->at(j,i).green=
                    dmap->at(j,i).blue=shade;
                }
            }
        }
    }
}

Comrade::Iris3D::DepthmapBuilder::~DepthmapBuilder()
{}
